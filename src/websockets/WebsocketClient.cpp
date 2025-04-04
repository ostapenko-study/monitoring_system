#include "WebsocketClient.h"
#include "ClientConfig.h"
#include "Common.h"
#include <QJsonObject>

std::map<WebsocketClient::Role, QString> WebsocketClient::role_to_str = {
        {Role::Sender, "sender"},
        {Role::Proxy, "proxy"},
        {Role::Agent, "agent"},
    };

WebsocketClient::WebsocketClient(QObject* parent)
    : QObject(parent)
{
    m_socket = new QWebSocket;
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
        pkg.insert("key", m_key);
        pkg.insert("role", roleToStr(m_role));
        pkg.insert("data", msg);

        qint64 len = m_socket->sendTextMessage(QJsonDocument(pkg).toJson(QJsonDocument::Compact));

        m_socket->flush();

        if(len != msg.size())
        {
            qWarning() << "Error while sending data via socket!";
        }else{
            qInfo() <<  "sended" << msg;
        }
    }
    else
    {
        qWarning() << "socket isn't open";
    }
}

WebsocketClient* createWebsocketClient(const WebsocketClient::Role role)
{
    const auto config = ClientConfig::generateFromFile();

    auto client = new WebsocketClient;

    client->setRole(role);

    client->setKey(generator::machineId());

    client->setUrl(config.url());

    return client;
}
