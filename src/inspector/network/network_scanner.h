#ifndef NETWORK_SCANNER_H
#define NETWORK_SCANNER_H

#include "qhostaddress.h"
#include <QPair>
#include <vector>
#include <string>
#include <optional>

namespace network_scanner
{
bool ping_host(const std::string& host);

QList<QHostAddress> get_docker_container_ips();

QList<QHostAddress> scan_network(QHostAddress base_ip, QHostAddress mask);

QJsonArray hostAddressListToJsonArray(const QList<QHostAddress> &addresses);

QHostAddress get_network_address(const QHostAddress& ip, const QHostAddress& netmask);

int get_available_hosts(QHostAddress netmask);

struct InterfaceInfo {
    QString name;
    QHostAddress ip;
    QHostAddress netmask;
    QString mac;

    QString toString() const;

    QJsonObject toJson() const;

    QList<QHostAddress> scan() const;

    bool containsHost(const QString& hostStr) const; //gpt
};


QList<InterfaceInfo> get_interfaces();
std::optional<InterfaceInfo> find_interface_by_ip(const QString& ip);

struct Interfaces
{
    QList<QPair<InterfaceInfo, QList<QHostAddress>>> data;

    QJsonArray toJson() const;
};

Interfaces get_full_interfaces();

}

#endif // NETWORK_SCANNER_H
