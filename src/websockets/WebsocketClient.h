#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QPointer>

class WebsocketClient
{
public:
    WebsocketClient();
    virtual ~WebsocketClient();

    void setKey(const QString& key);

    void setRole(const QString& role);

    void setUrl(const QUrl& server);

    void sendMessage(const QString& msg);

signals:

protected:
    QString mRole;
    QString mKey;
    QPointer<QWebSocket> mSocket;
};

WebsocketClient createWebsocketClient(const QString& role);

#endif // WEBSOCKETCLIENT_H
