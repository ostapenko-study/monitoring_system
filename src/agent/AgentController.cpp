#include "AgentController.h"
#include "websockets_common.h"

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
    m_client->sendMessage(json::toString(obj));
}

void AgentController::onClientReceivedMessage(QString text)
{

}
