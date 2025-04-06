#include "ClientConfig.h"
#include <QJsonObject>
#include "websockets_common.h"

ClientConfig ClientConfig::generateFromFile(const QString &config_filename)
{
    ClientConfig answer;

    const auto config_object =
        json::toJson(
            file::read(
                config_filename
            )
        ).object();

    answer.server_ip = config_object.value("server_ip").toString();
    answer.server_port = config_object.value("server_port").toInt();

    return answer;
}

QUrl ClientConfig::url() const
{
    return QUrl(
            QString("ws://%1:%2")
                .arg(server_ip)
                .arg(server_port)
        );
}
