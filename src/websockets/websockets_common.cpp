#include "websockets_common.h"
#include "qjsonobject.h"
#include <QFile>
#include <QDebug>
#include <QWebSocket>

QByteArray file::read(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file:" << file.errorString();
        throw std::logic_error("failed to open file");
    }

    QByteArray data = file.readAll();
    file.close();

    return data;
}

void file::write(const QString &filename, const QString &data)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << data;
    }
    file.flush();
    file.close();
}

QString generator::machineId()
{
    return QString(file::read("/etc/machine-id"));
}

bool websocket::sendTextMessage(QWebSocket *socket, const QString &message)
{
    qint64 len = socket->sendTextMessage(message);

    socket->flush();

    if(len != message.size())
    {
        qWarning() << "Error while sending data via socket!";
        return false;
    }else{
        qInfo() <<  "sended" << socket->localAddress() << socket->localPort() << "message:"<< message;
        return true;
    }
}

QJsonDocument json::toJson(const QByteArray &data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if(jsonDoc.isNull())
    {
        qWarning() << "Failed to parse JSON";
        throw std::logic_error("failed to parse JSON");
    }
    return jsonDoc;
}

QString json::toString(const QJsonObject &obj)
{
    return QString(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

QJsonObject json::parseStr(const QString &msg)
{
    return QJsonDocument::fromJson(msg.toUtf8()).object();
}
