#include "ClientConfig.h"
#include <QJsonObject>
#include "websockets_common.h"

const QString ClientConfig::default_config_file = "./client.conf";

QJsonObject ClientConfig::toJson() const
{
    QJsonObject answer;

    answer["server_ip"] = server_ip;
    answer["server_port"] = server_port;
    answer["client_key"] = client_key;

    return answer;
}

ClientConfig ClientConfig::fromJson(const QJsonObject &obj)
{
    ClientConfig answer;

    answer.server_ip = obj.value("server_ip").toString();
    answer.server_port = obj.value("server_port").toInt();
    answer.client_key = obj.value("client_key").toString();

    return answer;
}

ClientConfig ClientConfig::generateFromFile(const QString &config_filename)
{
    return ClientConfig::fromJson(
            json::toJson(
                file::read(
                    config_filename
                )
            ).object()
        );
}

QUrl ClientConfig::url() const
{
    return QUrl(
            QString("ws://%1:%2")
                .arg(server_ip)
                .arg(server_port)
        );
}

QString ClientConfig::clientKey() const
{
    return generator::machineId() + "; " + client_key;
}
