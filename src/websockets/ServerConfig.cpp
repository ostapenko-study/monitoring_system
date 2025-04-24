#include "ServerConfig.h"
#include <QJsonObject>
#include "websockets_common.h"

ServerConfig ServerConfig::generateFromFile(const QString &config_filename)
{
    ServerConfig answer;

    const auto config_object =
        json::toJson(
            file::read(
                config_filename
                )
            ).object();

    answer.server_name = config_object.value("server_name").toString();
    answer.port = config_object.value("port").toInt();

    return answer;
}

QJsonObject ServerConfig::toJson() const
{
    QJsonObject answer;

    answer["server_name"] = server_name;
    answer["port"] = port;

    return answer;
}

QString ServerConfig::serverName() const
{
    return generator::machineId() + "; " + server_name;
}
