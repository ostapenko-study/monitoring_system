#ifndef AGENTCONTROLLER_H
#define AGENTCONTROLLER_H

#include <QObject>
#include "WebsocketClient.h"
#include "AgentWorker.h"

class AgentController : public QObject
{
    Q_OBJECT
public:
    explicit AgentController(QObject *parent = nullptr);

    void init();

signals:

protected:
    WebsocketClient* m_client;
    AgentWorker* m_worker;
};

#endif // AGENTCONTROLLER_H
