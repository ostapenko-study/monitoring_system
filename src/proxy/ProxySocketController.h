#ifndef PROXYSOCKETCONTROLLER_H
#define PROXYSOCKETCONTROLLER_H

#include <QObject>
#include "WebsocketClient.h"
#include "WebsocketServer.h"
#include "websockets_common.h"

class ProxySocketController : public QObject
{
    Q_OBJECT
public:
    explicit ProxySocketController(QObject *parent = nullptr);

    GET_SET_POINTER(WebsocketServer, Server)
    GET_SET_POINTER(WebsocketClient, Client)

    void init();

signals:
    void commandReceived(QJsonObject pkg);
protected:
    void onServerReceivedMessage(QJsonObject message);
    void onClientReceivedMessage(QString message);
    QJsonObject processMessage(QJsonObject data);

    QJsonObject getTopBySshRequest(const QJsonObject& );
    QJsonObject getScanRequest(const QJsonObject& );
    QJsonObject setupDeviceBySshRequest(const QJsonObject& );


    using HandlerFunc = QJsonObject (ProxySocketController::*)(const QJsonObject&);
    static const QMap<QString, HandlerFunc> m_command_to_implement;

};

#endif // PROXYSOCKETCONTROLLER_H
