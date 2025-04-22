#include "network_scanner.h"
#include "qjsonobject.h"
#include <future>
#include <QDebug>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <QHostAddress>
#include <vector>
#include <future>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <QJsonArray>

bool network_scanner::ping_host(const std::string &host) {
    std::string cmd = "ping -c 1 -W 1 " + host + " > /dev/null 2>&1";
    int result = std::system(cmd.c_str());
    return result == 0;
}

QList<network_scanner::InterfaceInfo> network_scanner::get_interfaces()
{
    QList<InterfaceInfo> list;
    ifaddrs *ifaddr, *ifa;
    getifaddrs(&ifaddr);

    for (ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) continue;
        if (!(ifa->ifa_flags & IFF_UP)) continue;

        InterfaceInfo info;
        info.name = QString::fromUtf8(ifa->ifa_name);

        auto *addr = (sockaddr_in *)ifa->ifa_addr;
        info.ip = QHostAddress(ntohl(addr->sin_addr.s_addr));

        if (ifa->ifa_netmask) {
            auto *net = (sockaddr_in *)ifa->ifa_netmask;
            info.netmask = QHostAddress(ntohl(net->sin_addr.s_addr));
        }

        for (ifaddrs *ifa2 = ifaddr; ifa2; ifa2 = ifa2->ifa_next) {
            if (ifa2->ifa_addr && ifa2->ifa_addr->sa_family == AF_PACKET &&
                QString(ifa2->ifa_name) == info.name) {
                auto *s = (sockaddr_ll *)ifa2->ifa_addr;
                if (s->sll_halen == 6) {
                    info.mac = QString("%1:%2:%3:%4:%5:%6")
                                   .arg(s->sll_addr[0], 2, 16, QChar('0'))
                                   .arg(s->sll_addr[1], 2, 16, QChar('0'))
                                   .arg(s->sll_addr[2], 2, 16, QChar('0'))
                                   .arg(s->sll_addr[3], 2, 16, QChar('0'))
                                   .arg(s->sll_addr[4], 2, 16, QChar('0'))
                                   .arg(s->sll_addr[5], 2, 16, QChar('0'));
                }
            }
        }

        list.append(info);
    }

    freeifaddrs(ifaddr);
    return list;
}

QString network_scanner::InterfaceInfo::toString() const {
    return QString("Інтерфейс: %1\n  IP: %2\n  Маска: %3\n  MAC: %4")
        .arg(name)
        .arg(ip.toString())
        .arg(netmask.toString())
        .arg(mac.isEmpty() ? "невідомий" : mac);
}

QJsonObject network_scanner::InterfaceInfo::toJson() const {
    QJsonObject obj;
    obj["name"] = name;
    obj["ip"] = ip.toString();
    obj["netmask"] = netmask.toString();
    obj["mac"] = mac;
    return obj;
}

QList<QHostAddress> network_scanner::InterfaceInfo::scan() const
{
    if(name.startsWith("docker")){
        qInfo() << "for interface" << name << "returned get_network_address";
        return get_docker_container_ips();
    }
    return scan_network(get_network_address(ip, netmask), netmask);
}

bool network_scanner::InterfaceInfo::containsHost(const QString &hostStr) const {
    QHostAddress hostAddr(hostStr);
    if (hostAddr.protocol() != ip.protocol()) {
        return false; // IPv4 vs IPv6 mismatch
    }

    // Convert addresses to quint32 (only works for IPv4)
    if (ip.protocol() == QAbstractSocket::IPv4Protocol) {
        quint32 ipInt = ip.toIPv4Address();
        quint32 netmaskInt = netmask.toIPv4Address();
        quint32 networkBase = ipInt & netmaskInt;
        quint32 hostInt = hostAddr.toIPv4Address();
        quint32 hostNetworkBase = hostInt & netmaskInt;

        return networkBase == hostNetworkBase;
    }

    // Optional: add IPv6 handling here if потрібно
    return false;
}

int network_scanner::get_available_hosts(QHostAddress netmask) {
    // Перетворюємо маску підмережі в uint32_t
    uint32_t netmask_uint = netmask.toIPv4Address();

    // Підраховуємо кількість бітів для хостів (0-біти)
    uint32_t host_bits = ~netmask_uint;

    // Підраховуємо кількість доступних хостів (2^host_bits - 2)
    int num_hosts = (1 << __builtin_popcount(host_bits)) - 2;

    return num_hosts;
}

std::mutex mtx;  // М'ютекс для синхронізації доступу до лічильників потоків
std::condition_variable cv;  // Умовна змінна для очікування, коли зменшиться кількість активних потоків

int active_threads = 0;  // Лічильник активних потоків
const int max_threads = 50;  // Максимальна кількість одночасних потоків

QList<QHostAddress> network_scanner::scan_network(QHostAddress base_ip, QHostAddress mask)
{
    qDebug() << "scan_network" << base_ip << mask;
    std::vector<std::future<std::pair<QHostAddress, bool>>> futures;
    QList<QHostAddress> alive_hosts;

    uint32_t base_ip_uint = base_ip.toIPv4Address();

    const int count = get_available_hosts(mask);

    for (int i = 1; i <= count; ++i) {
        uint32_t ip_uint = base_ip_uint + i;
        QHostAddress ip;
        ip.setAddress(ip_uint);

        // Чекаємо, поки кількість активних потоків не зменшиться
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []() { return active_threads < max_threads; });
            ++active_threads;  // Збільшуємо кількість активних потоків
        }

        futures.emplace_back(std::async(std::launch::async, [ip]() {
            bool alive = ping_host(ip.toString().toStdString());
            {
                std::lock_guard<std::mutex> lock(mtx);  // Синхронізуємо доступ до активних потоків
                --active_threads;  // Зменшуємо кількість активних потоків
            }
            cv.notify_one();  // Сповіщаємо, що один потік завершився
            return std::make_pair(ip, alive);
        }));
    }

    for (auto &fut : futures) {
        auto [ip, alive] = fut.get();
        if (alive) {
            alive_hosts.append(ip); // Додаємо живий хост в результат
        }
    }

    return alive_hosts;
}

QHostAddress network_scanner::get_network_address(const QHostAddress &ip, const QHostAddress &netmask) {
    uint32_t ip_uint = ip.toIPv4Address();         // Перетворюємо IP в uint32_t
    uint32_t netmask_uint = netmask.toIPv4Address(); // Перетворюємо маску в uint32_t

    uint32_t network_address_uint = ip_uint & netmask_uint; // Виконуємо логічне AND

    QHostAddress network_address;
    network_address.setAddress(network_address_uint); // Встановлюємо результат як IP

    return network_address;
}

QList<QHostAddress> network_scanner::get_docker_container_ips() {
    qDebug() << "get_docker_container_ips";
    QList<QHostAddress> ips;

    // Виконуємо команду `docker ps -q | xargs -I {} docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' {}`
    std::string command = "docker ps -q | xargs -I {} docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' {}";

    // Використовуємо popen для виконання команди і захоплення результату
    std::array<char, 128> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        std::cerr << "Не вдалося виконати команду" << std::endl;
        return ips;
    }

    // Читаємо вихідний потік команди і додаємо IP-адреси в вектор
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        std::string ip_str(buffer.data());
        ip_str.erase(ip_str.find_last_not_of(" \n\r\t") + 1); // Видаляємо зайві пробіли та символи нового рядка

        if (!ip_str.empty()) {
            // Перетворюємо string в QHostAddress і додаємо в список
            QHostAddress ip(ip_str.c_str());
            ips.append(ip);
        }
    }

    return ips;
}

network_scanner::Interfaces network_scanner::get_full_interfaces()
{
    Interfaces answer;

    const auto interfaces = network_scanner::get_interfaces();
    for (const auto& interface : interfaces) {
        if(
            interface.name == "lo"
            ||
            interface.name.startsWith("br-") //linux system networks-bridge (for docker for example)
        ){
            answer.data.push_back({interface, {}});
        }else{
            answer.data.push_back({interface, interface.scan()});
        }
    }

    return answer;
}

QJsonArray network_scanner::Interfaces::toJson() const
{
    QJsonArray answer;

    for(auto it = data.begin(); it != data.end(); ++it){
        QJsonObject obj = it->first.toJson();
        obj["addresses"] = hostAddressListToJsonArray(it->second);
        answer.push_back(obj);
    }

    return answer;
}

QJsonArray network_scanner::hostAddressListToJsonArray(const QList<QHostAddress> &addresses) {
    QJsonArray jsonArray;
    for (const QHostAddress &address : addresses) {
        jsonArray.append(address.toString());
    }
    return jsonArray;
}

std::optional<network_scanner::InterfaceInfo> network_scanner::find_interface_by_ip(const QString &ip)
{
    auto interfaces = network_scanner::get_interfaces();
    foreach (const auto& interface, interfaces) {
        if(interface.containsHost(ip)){
            return interface;
        }
    }

    return std::nullopt;
}
