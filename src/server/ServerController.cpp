#include "ServerController.h"
#include "websockets_common.h"
#include "CommandHandler.h"


const QMap<QString, ServerController::HandlerFunc> ServerController::m_command_to_implement = {
    {"get_top_by_ssh", &ServerController::getTopBySshRequest},
    {"get_scan", &ServerController::getScanRequest},
    {"setup_device_by_ssh", &ServerController::setupDeviceBySshRequest},
    };

ServerController::ServerController(QObject *parent)
    : QObject{parent}
{

}

void ServerController::onServerSystemReceived(QJsonObject data)
{
    m_server_view->sendMessageToAll(json::toString(data));
}

void ServerController::onServerViewReceived(QJsonObject obj)
{
    const auto data = obj.value("data").toObject();
    if(obj.contains("to")){ //as proxy
        m_server_system->sendMessage(
            json::toString(data),
            obj.value("to").toString()
        );
    }else{
        auto answer = processMessage(obj);

        answer["index"] = obj.value("index");

        m_server_view->sendMessageToAll(json::toString(answer));
    }
}

QJsonObject ServerController::processMessage(QJsonObject data)
{
    const auto command = data.value("command").toString();

    if(!m_command_to_implement.contains(command))
    {
        return json::generateError("command not find");
    }

    auto func = m_command_to_implement[command];
    return (this->*func)(data.value("data").toObject());
}


QJsonObject ServerController::getTopBySshRequest(const QJsonObject & data)
{
    return json::generateResult(command_handler::getTopRequestBySsh(data));
}

QJsonObject ServerController::getScanRequest(const QJsonObject & data)
{
    return json::generateResult(command_handler::getScanNetworkRequest(data));
}

QJsonObject ServerController::setupDeviceBySshRequest(const QJsonObject & data)
{
    return json::generateResult(command_handler::setupDeviceBySsh(data, m_server_system->port()));
}
