#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QPointer>

class WebsocketClient
    : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketClient(QObject* parent = nullptr);
    virtual ~WebsocketClient();

    void setKey(const QString& key);

    enum class Role
    {
        Sender,
        Proxy,
        Agent,
        Server,
        View,
    };

    static std::map<Role, QString> role_to_str;
    static std::map<QString, Role> generateStrToRole();
    static QString roleToStr(const Role role);
    static Role strToRole(const QString& role);

    void setRole(const Role role);

    void setUrl(const QUrl& server);

    void sendMessage(const QString& msg);

signals:
    void received(QString message);
protected:
    Role m_role;
    QString m_key;
    QPointer<QWebSocket> m_socket;
};

QString getClientWebsocketConfigFileNameByRole(const WebsocketClient::Role role);

WebsocketClient* createWebsocketClient(const WebsocketClient::Role role);

#endif // WEBSOCKETCLIENT_H
