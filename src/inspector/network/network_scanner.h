#ifndef NETWORK_SCANNER_H
#define NETWORK_SCANNER_H

#include "qhostaddress.h"
#include <vector>
#include <string>

namespace network_scanner
{
bool ping_host(const std::string& host);

QList<QHostAddress> get_docker_container_ips();

QList<QHostAddress> scan_network(QHostAddress base_ip, QHostAddress mask);

QHostAddress get_network_address(const QHostAddress& ip, const QHostAddress& netmask);

int get_available_hosts(QHostAddress netmask);

struct InterfaceInfo {
    QString name;
    QHostAddress ip;
    QHostAddress netmask;
    QString mac;

    QString toString() const;

    QList<QHostAddress> scan() const;
};


QList<InterfaceInfo> get_interfaces();

}

#endif // NETWORK_SCANNER_H
