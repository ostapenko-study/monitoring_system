#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <QJsonObject>
#include <QString>

struct ServerConfig
{
    QString server_name;
    int port;

    static ServerConfig generateFromFile(const QString& config_filename);

    QJsonObject toJson() const;

    QString serverName() const;

};

#endif // SERVERCONFIG_H
