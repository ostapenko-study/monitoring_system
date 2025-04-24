#include "ProxySocketController.h"
#include "CommandHandler.h"

const QMap<QString, ProxySocketController::HandlerFunc> ProxySocketController::m_command_to_implement = {
    {"get_top_by_ssh", &ProxySocketController::getTopBySshRequest},
    {"get_scan", &ProxySocketController::getScanRequest},
    {"setup_device_by_ssh", &ProxySocketController::setupDeviceBySshRequest},
};

ProxySocketController::ProxySocketController(QObject *parent)
    : QObject{parent}
{

}

void ProxySocketController::init()
{
    connect(getServer(), &WebsocketServer::received,
            this, &ProxySocketController::onServerReceivedMessage);
    connect(getClient(), &WebsocketClient::received,
            this, &ProxySocketController::onClientReceivedMessage);
}

void ProxySocketController::onServerReceivedMessage(QJsonObject message)
{
    getClient()->sendMessage(json::toString(message));
}

void ProxySocketController::onClientReceivedMessage(QString message)
{
    auto obj = json::parseStr(message);
    const auto data = obj.value("data").toObject();
    if(obj.contains("to")){ //as proxy
        getServer()->sendMessage(
            json::toString(data),
            obj.value("to").toString()
        );
    }else{
        auto answer = processMessage(obj);

        answer["index"] = obj.value("index");

        getClient()->sendMessage(json::toString(answer));
    }
}

QJsonObject ProxySocketController::processMessage(QJsonObject data)
{
    const auto command = data.value("command").toString();

    if(!m_command_to_implement.contains(command))
    {
        return json::generateError("command not find");
    }

    auto func = m_command_to_implement[command];
    return (this->*func)(data.value("data").toObject());
}

QJsonObject ProxySocketController::getTopBySshRequest(const QJsonObject & data)
{
    return json::generateResult(command_handler::getTopRequestBySsh(data));
}

QJsonObject ProxySocketController::getScanRequest(const QJsonObject & data)
{
    return json::generateResult(command_handler::getScanNetworkRequest(data));

}

QJsonObject ProxySocketController::setupDeviceBySshRequest(const QJsonObject & data)
{
    return json::generateResult(command_handler::setupDeviceBySsh(data, getServer()->port()));
}
