#include "AgentController.h"
#include "network/network_scanner.h"
#include "websockets_common.h"
#include "stat/TopStat.h"

const QMap<QString, AgentController::HandlerFunc> AgentController::m_command_to_implement = {
    {"set_config", &AgentController::setConfigRequest},
    {"get_top", &AgentController::getTopRequest},
    {"get_scan", &AgentController::getScanRequest},
};

AgentController::AgentController(QObject *parent)
    : QObject{parent}
{
    m_client = createWebsocketClient(WebsocketClient::Role::Agent);
    m_worker = createAgentWorker();

    connect(m_worker, &AgentWorker::packageCreated,
            this, &AgentController::onWorkerCreatedMessage);

    connect(m_client, &WebsocketClient::received,
            this, &AgentController::onClientReceivedMessage);

}

void AgentController::init()
{
    m_worker->start();
}

void AgentController::onWorkerCreatedMessage(QJsonObject obj)
{
    obj.insert("index", "monitoring_package_by_timer");
    m_client->sendMessage(json::toString(obj));
}

void AgentController::onClientReceivedMessage(QString text)
{
    QJsonObject obj = json::parseStr(text);

    auto answer = processMessage(obj);

    answer["index"] = obj.value("index");

    m_client->sendMessage(json::toString(answer));
}

QJsonObject AgentController::processMessage(QJsonObject data)
{
    const auto command = data.value("command").toString();

    if(!m_command_to_implement.contains(command))
    {
        return json::generateError("command not find");
    }

    auto func = m_command_to_implement[command];
    return (this->*func)(data.value("data").toObject());
}

QJsonObject AgentController::setConfigRequest(const QJsonObject &data)
{
    m_worker->setConfig(AgentConfig::createFromJson(data));
    m_worker->start();
    return json::resultOk;
}

QJsonObject AgentController::getTopRequest(const QJsonObject& )
{
    const auto stats = getProcessTopInfos();
    QJsonObject answer;
    answer["top"] = json::containerToJson(stats.begin(), stats.end());
    return json::generateResult(answer);
}

QJsonObject AgentController::getScanRequest(const QJsonObject &)
{
    QJsonObject answer;
    answer["interfaces"] = network_scanner::get_full_interfaces().toJson();
    return json::generateResult(answer);

}
