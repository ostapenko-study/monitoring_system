#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include <QObject>
#include "WebsocketServer.h"

class ServerController : public QObject
{
    Q_OBJECT
public:
    explicit ServerController(QObject *parent = nullptr);

    void setServerView(WebsocketServer* ptr) {m_server_view = ptr;}
    void setServerSystem(WebsocketServer* ptr) {m_server_system = ptr;}

signals:

protected:
    void onServerSystemReceived(QJsonObject data);
    void onServerViewReceived(QJsonObject data);

    WebsocketServer* m_server_view;
    WebsocketServer* m_server_system;

    QJsonObject processMessage(QJsonObject data);

    QJsonObject getTopBySshRequest(const QJsonObject& );
    QJsonObject getScanRequest(const QJsonObject& );
    QJsonObject setupDeviceBySshRequest(const QJsonObject& );


    using HandlerFunc = QJsonObject (ServerController::*)(const QJsonObject&);
    static const QMap<QString, HandlerFunc> m_command_to_implement;
};

#endif // SERVERCONTROLLER_H
