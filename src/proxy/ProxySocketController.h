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
};

#endif // PROXYSOCKETCONTROLLER_H
