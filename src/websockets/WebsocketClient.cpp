#include "WebsocketClient.h"
#include "ClientConfig.h"
#include "Common.h"
#include <QJsonObject>

WebsocketClient::WebsocketClient()
{
    mSocket = new QWebSocket;
}

WebsocketClient::~WebsocketClient()
{
    if(mSocket)
    {
        mSocket->deleteLater();
    }
}

void WebsocketClient::setKey(const QString &key)
{
    mKey = key;
}

void WebsocketClient::setRole(const QString &role)
{
    mRole = role;
}

void WebsocketClient::setUrl(const QUrl &url)
{
    qInfo() << "try to open socket:" << url;
    mSocket->open(url);
}

void WebsocketClient::sendMessage(const QString &msg)
{
    qInfo() << "try to send message:" << msg;
    if(mSocket->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        QJsonObject pkg;
        pkg.insert("key", mKey);
        pkg.insert("role", mRole);
        pkg.insert("data", msg);

        qint64 len = mSocket->sendTextMessage(QJsonDocument(pkg).toJson(QJsonDocument::Compact));

        mSocket->flush();

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

WebsocketClient createWebsocketClient(const QString &role)
{
    const auto config = ClientConfig::generateFromFile();

    WebsocketClient client;

    client.setRole(role);

    client.setKey(generator::machineId());

    client.setUrl(config.url());

    return client;
}
