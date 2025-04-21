#include "CommandHandler.h"
#include "network/network_scanner.h"
#include "websockets_common.h"
#include "stat/MainStat.h"

namespace command_handler
{

QJsonObject& appendIndex(QJsonObject &output, const QJsonObject &request)
{
    output["index"] = request.value("index");
    return output;
}


QJsonObject getTopRequest(const QJsonObject& data)
{
    const auto stats = getProcessTopInfos();
    QJsonObject answer;
    answer["top"] = json::containerToJson(stats.begin(), stats.end());
    return json::generateResult(appendIndex(answer, data));
}

QJsonObject getScanNetworkRequest(const QJsonObject& data)
{
    QJsonObject answer;
    answer["interfaces"] = network_scanner::get_full_interfaces().toJson();
    return json::generateResult(appendIndex(answer, data));
}

QJsonObject getTopRequestBySsh(const QJsonObject & data)
{
    const auto stats = getProcessTopInfosBySsh(SshCredentials::fromJson(data));
    QJsonObject answer;
    answer["top"] = json::containerToJson(stats.begin(), stats.end());
    return json::generateResult(appendIndex(answer, data));
}

QJsonObject setupDeviceBySsh(const QJsonObject& data)
{

}

}
