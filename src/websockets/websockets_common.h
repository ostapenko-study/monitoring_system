#pragma once

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
    void write(const QString &filename, const QString &data);
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
    QJsonDocument toJson(const QByteArray& data);
    QString toString(const QJsonObject& obj);
    QJsonObject parseStr(const QString& msg);
}

