#include "AgentController.h"
#include "CommandHandler.h"
#include "websockets_common.h"

const QMap<QString, AgentController::HandlerFunc> AgentController::m_command_to_implement = {
    {"set_config", &AgentController::setConfigRequest},
    {"get_top", &AgentController::getTopRequest},
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
    auto answer = QJsonObject{};
    return json::generateResult(command_handler::appendIndex(answer, data));
}

QJsonObject AgentController::getTopRequest(const QJsonObject& data)
{
    return json::generateResult(command_handler::getTopRequest(data));
}
