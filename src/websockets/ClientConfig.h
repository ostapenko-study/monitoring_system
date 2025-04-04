#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H

#include <QString>
#include <QUrl>

struct ClientConfig
{
    QString server_ip;
    int server_port;

    static ClientConfig generateFromFile(const QString& config_filename = "./client.conf");

    QUrl url() const;
};


#endif // CLIENTCONFIG_H
