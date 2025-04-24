#include "AgentConfig.h"
#include <QJsonArray>
#include "websockets_common.h"


const QString AgentConfig::default_config_filename = "./agent.conf";

AgentConfig AgentConfig::createFromJson(const QJsonObject & obj)
{
    AgentConfig answer;

#define PARSE_ARRAY(key) { \
    auto key##arr = obj.value(#key).toArray(); \
        answer.key.reserve(key##arr.size()); \
        foreach (const auto& obj, key##arr) { \
            answer.key.push_back(obj.toString().toStdString()); \
    } \
}
    PARSE_ARRAY(users);
    PARSE_ARRAY(processes);
#undef PARSE_ARRAY

    answer.timeout = obj.value("timeout").toInt();

    return answer;
}

QJsonObject AgentConfig::toJson() const
{
    QJsonObject answer;

#define INSERT_ARRAY(key) { \
    auto key##arr = QJsonArray(); \
    for(const auto& var: key){\
        key##arr.append(QString::fromStdString(var)); \
    }\
}
    INSERT_ARRAY(users);
    INSERT_ARRAY(processes);
#undef INSERT_ARRAY

    answer.insert("timeout", timeout);

    return answer;
}

AgentConfig AgentConfig::generateFromFile(const QString &config_filename)
{
    const auto config_object =
        json::toJson(
            file::read(
                config_filename
                )
            ).object();

    return createFromJson(config_object);
}

void AgentConfig::saveToFile(const QString &config_filename) const
{
    file::write(config_filename, json::toString(toJson()));
}
