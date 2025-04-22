#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H

#include <QString>
#include <QUrl>
#include <QJsonObject>

struct ClientConfig
{
    QString client_key;

    QString server_ip;
    int server_port;

    QJsonObject toJson() const;

    static const QString default_config_file;

    static ClientConfig fromJson(const QJsonObject& obj);
    static ClientConfig generateFromFile(const QString& config_filename = default_config_file);

    QUrl url() const;

    QString clientKey() const;
};


#endif // CLIENTCONFIG_H
