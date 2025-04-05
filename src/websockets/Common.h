#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QJsonDocument>

#define GET_SET_POINTER(type, name) \
private: \
type* m##name = nullptr; \
public: \
void set##name(type* var) {m##name = var;} \
type* get##name() const {return m##name;}

namespace file
{
    QByteArray read(const QString &filename);
    QJsonDocument toJson(const QByteArray& data);
}

namespace generator
{
    QString machineId();
}

class QWebSocket;

namespace websocket
{
    bool sendTextMessage(QWebSocket* socket, const QString& message);
}

namespace json
{
    QString toString(const QJsonObject& obj);
    QJsonObject parseStr(const QString& msg);
}
#endif // COMMON_H
