#include "WebsocketClient.h"
#include "ClientConfig.h"
#include "websockets_common.h"
#include <QJsonObject>

std::map<WebsocketClient::Role, QString> WebsocketClient::role_to_str = {
        {Role::Sender, "sender"},
        {Role::Proxy, "proxy"},
        {Role::Agent, "agent"},
        {Role::Server, "server"},
        {Role::View, "view"},
    };

WebsocketClient::WebsocketClient(QObject* parent)
    : QObject(parent)
{
    m_socket = new QWebSocket;

    connect(m_socket, &QWebSocket::textMessageReceived,
            this, &WebsocketClient::received);
}

WebsocketClient::~WebsocketClient()
{
    if(m_socket)
    {
        m_socket->deleteLater();
    }
}

void WebsocketClient::setKey(const QString &key)
{
    m_key = key;
}

std::map<QString, WebsocketClient::Role> WebsocketClient::generateStrToRole()
{
    std::map<QString, WebsocketClient::Role> answer;

    for(auto it = role_to_str.begin(); it != role_to_str.end(); ++it)
    {
        answer.insert({it->second, it->first});
    }

    return answer;
}

QString WebsocketClient::roleToStr(const Role role)
{
    return role_to_str.at(role);
}

WebsocketClient::Role WebsocketClient::strToRole(const QString &role)
{
    static std::map<QString, WebsocketClient::Role> str_to_role = generateStrToRole();
    return str_to_role.at(role);
}

void WebsocketClient::setRole(const Role role)
{
    m_role = role;
}

void WebsocketClient::setUrl(const QUrl &url)
{
    qInfo() << "try to open socket:" << url;
    m_socket->open(url);
}

void WebsocketClient::sendMessage(const QString &msg)
{
    qInfo() << "try to send message:" << msg;
    if(m_socket->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        QJsonObject pkg;
        pkg.insert("from", m_key);
        pkg.insert("key", m_key);
        pkg.insert("role", roleToStr(m_role));
        pkg.insert("data", msg);

        websocket::sendTextMessage(m_socket, json::toString(pkg));

    }
    else
    {
        qWarning() << "socket isn't open";
    }
}

QString getClientWebsocketConfigFileNameByRole(const WebsocketClient::Role role)
{
    static const std::map<WebsocketClient::Role, QString> __data = {
        {WebsocketClient::Role::Agent, "agent_websocket_client.conf"},
        {WebsocketClient::Role::Proxy, "proxy_websocket_client.conf"},
        {WebsocketClient::Role::Sender, "sender_websocket_client.conf"},
        {WebsocketClient::Role::Server, "server_websocket_client.conf"},
    };

    return __data.at(role);
}

WebsocketClient* createWebsocketClient(const WebsocketClient::Role role)
{
    const auto config = ClientConfig::generateFromFile(getClientWebsocketConfigFileNameByRole(role));

    auto client = new WebsocketClient;

    client->setRole(role);

    client->setKey(config.clientKey());

    client->setUrl(config.url());

    return client;
}

