#include "ServerConfig.h"
#include <QJsonObject>
#include "Common.h"

ServerConfig ServerConfig::generateFromFile(const QString &config_filename)
{
    ServerConfig answer;

    const auto config_object =
        file::toJson(
            file::read(
                config_filename
                )
            ).object();

    answer.server_name = config_object.value("server_name").toString(generator::machineId());
    answer.port = config_object.value("port").toInt();

    return answer;
}
