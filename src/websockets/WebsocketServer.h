#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QPointer>
#include <QJsonObject>

#include "ServerConfig.h"

class WebsocketServer: public QObject
{
    Q_OBJECT
public:
    explicit WebsocketServer(const ServerConfig& model, QObject* parent = nullptr);

    void sendMessage(const QString& message, const QString& key);
    void sendMessageToAll(const QString& message);

    enum class Role
    {
        Proxy,
        ServerSystem,
        ServerView,
    };

    int port() const;
signals:
    void received(QJsonObject pkg, QString socket_key);
    void disconnected(QString socket_key);
    void closed();
protected:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void onSocketDisconnected();

    void printDebugMessage(QString text) const;

    void onClosed();

    const QString m_key;

    QWebSocketServer* const m_server;

    std::map<QString, QPointer<QWebSocket>> m_key_to_socket;
    std::map<QWebSocket*, QString> m_socket_to_key;

    const ServerConfig m_config;
};

QString getServerWebsocketConfigFileNameByRole(const WebsocketServer::Role role);

WebsocketServer* createWebsocketServer(const WebsocketServer::Role role);

#endif // WEBSOCKETSERVER_H
