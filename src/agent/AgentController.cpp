#include "AgentController.h"

AgentController::AgentController(QObject *parent)
    : QObject{parent}
{
    m_client = createWebsocketClient(WebsocketClient::Role::Agent);
    m_worker = createAgentWorker();
}

void AgentController::init()
{
    m_worker->start();
}
