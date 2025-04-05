#include "WebsocketServer.h"
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include "WebsocketClient.h"
#include "Common.h"

WebsocketServer::WebsocketServer(const ServerConfig& config, QObject *parent)
    : QObject(parent)
    , m_server(new QWebSocketServer(config.server_name,
                                   QWebSocketServer::NonSecureMode, this))
{
    if(m_server->listen(QHostAddress::Any, config.port))
    {
        connect(m_server, &QWebSocketServer::newConnection,
                this, &WebsocketServer::onNewConnection);
        connect(m_server, &QWebSocketServer::closed,
                this, &WebsocketServer::onClosed);
    }
}

void WebsocketServer::sendMessage(const QString &message, const QString &key)
{
    if(!m_key_to_socket.count(key))
    {
        qWarning() << "try to send message \"" << message << "\"to socket with key" << key;
        return;
    }

    const auto socket = m_key_to_socket.at(key);

    if(!socket)
    {
        qWarning() << "socket with key" << key << "isn't alive";
        return;
    }

    websocket::sendTextMessage(socket, message);
}

void WebsocketServer::onNewConnection()
{
    auto socket = m_server->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &WebsocketServer::processTextMessage);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebsocketServer::processBinaryMessage);
    connect(socket, &QWebSocket::disconnected, this, &WebsocketServer::onSocketDisconnected);

}

void WebsocketServer::processTextMessage(QString message)
{
    auto client = qobject_cast<QWebSocket* >(sender());

    const auto obj = json::parseStr(message);

    const auto client_key = obj.value("key").toString();
    if(client_key.isEmpty())
    {
        qWarning() << "received text with empty key:" << message;
        return;
    }

    const auto str_role = obj.value("role").toString();
    if(str_role.isEmpty())
    {
        qWarning() << "received text with empty role:" << message;
        return;
    }

    const auto client_role = WebsocketClient::strToRole(str_role);
    if(
        QVector<WebsocketClient::Role>{
            WebsocketClient::Role::Agent,
            WebsocketClient::Role::Proxy,
        }.count(client_role)
        )
    {

        m_key_to_socket[client_key] = client;
    }

    emit received(obj);
}

void WebsocketServer::processBinaryMessage(QByteArray message)
{
    Q_UNUSED(message)

    qWarning() << "we send only text message";
}

void WebsocketServer::onSocketDisconnected()
{
    auto client = qobject_cast<QWebSocket* >(sender());

    const auto socket_key = m_socket_to_key.at(client);
    m_key_to_socket.erase(socket_key);
    m_socket_to_key.erase(client);

    emit disconnected(socket_key);
}

void WebsocketServer::onClosed()
{
    emit closed();
}

WebsocketServer* createWebsocketServer()
{
    auto answer = new WebsocketServer(ServerConfig::generateFromFile());

    return answer;
}
