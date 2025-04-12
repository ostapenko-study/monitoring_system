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
    void onWorkerCreatedMessage(QJsonObject obj);
    void onClientReceivedMessage(QString str);

    QJsonObject processMessage(QJsonObject data);

    QJsonObject setConfigRequest(const QJsonObject& data);
    QJsonObject getTopRequest(const QJsonObject& );
    QJsonObject getScanRequest(const QJsonObject& );


    using HandlerFunc = QJsonObject (AgentController::*)(const QJsonObject&);
    static const QMap<QString, HandlerFunc> m_command_to_implement;


    WebsocketClient* m_client;
    AgentWorker* m_worker;
};

#endif // AGENTCONTROLLER_H
