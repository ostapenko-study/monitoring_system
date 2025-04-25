#include "WebsocketServer.h"
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include "WebsocketClient.h"
#include "websockets_common.h"

WebsocketServer::WebsocketServer(const ServerConfig& config, QObject *parent)
    : QObject(parent)
    , m_server(new QWebSocketServer(config.serverName(),
                                   QWebSocketServer::NonSecureMode, this))
    , m_config{config}
{
    if(m_server->listen(QHostAddress::Any, config.port))
    {
        printDebugMessage("socket server open");
        connect(m_server, &QWebSocketServer::newConnection,
                this, &WebsocketServer::onNewConnection);
        connect(m_server, &QWebSocketServer::closed,
                this, &WebsocketServer::onClosed);
    }
    else
    {
        printDebugMessage("socket server open error");
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

void WebsocketServer::sendMessageToAll(const QString &message)
{
    printDebugMessage("send to all: " + message);
    printDebugMessage(QString("sockets count: %1").arg(m_key_to_socket.size()));
    for(auto it = m_key_to_socket.begin(); it != m_key_to_socket.end(); ++it)
    {
        websocket::sendTextMessage(it->second, message);
    }
}

int WebsocketServer::port() const
{
    return m_server->serverPort();
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

    printDebugMessage(QString("key %1; message: %2").arg(client_key).arg(message));

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
            WebsocketClient::Role::View,
        }.count(client_role)
        )
    {

        m_key_to_socket[client_key] = client;
    }

    emit received(obj, client_key);
}

void WebsocketServer::processBinaryMessage(QByteArray message)
{
    Q_UNUSED(message)

    qWarning() << "we send only text message";
}

void WebsocketServer::onSocketDisconnected()
{
    auto client = qobject_cast<QWebSocket* >(sender());

    if(!m_socket_to_key.count(client)){
        printDebugMessage("Client disconnected view ?");
        return;
    }

    const auto socket_key = m_socket_to_key.at(client);
    m_key_to_socket.erase(socket_key);
    m_socket_to_key.erase(client);

    emit disconnected(socket_key);
}

void WebsocketServer::printDebugMessage(QString text) const
{
    qDebug() << "printDebugMessage" << m_config.server_name << m_config.port << text;
}

void WebsocketServer::onClosed()
{
    emit closed();
}

QString getServerWebsocketConfigFileNameByRole(const WebsocketServer::Role role)
{
    static const std::map<WebsocketServer::Role, QString> __data = {
        {WebsocketServer::Role::Proxy, "proxy_websocket_server.conf"},
        {WebsocketServer::Role::ServerSystem, "server_system_websocket_server.conf"},
        {WebsocketServer::Role::ServerView, "server_view_websocket_server.conf"},
    };

    return __data.at(role);
}

WebsocketServer* createWebsocketServer(const WebsocketServer::Role role)
{
    auto answer = new WebsocketServer(ServerConfig::generateFromFile(getServerWebsocketConfigFileNameByRole(role)));

    return answer;
}
