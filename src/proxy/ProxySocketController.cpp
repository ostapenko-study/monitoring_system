#include "ProxySocketController.h"

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
    }else{ //command for proxy
        emit commandReceived(data);
    }
}
