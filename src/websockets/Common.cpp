#include "Common.h"
#include <QFile>
#include <QDebug>

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

QJsonDocument file::toJson(const QByteArray &data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if(jsonDoc.isNull())
    {
        qWarning() << "Failed to parse JSON";
        throw std::logic_error("failed to parse JSON");
    }
    return jsonDoc;
}

QString generator::machineId()
{
    return QString(file::read("/etc/machine-id"));
}
