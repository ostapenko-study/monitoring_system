#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QJsonDocument>

namespace file
{
    QByteArray read(const QString &filename);
    QJsonDocument toJson(const QByteArray& data);
}

namespace generator
{
    QString machineId();
}

#endif // COMMON_H
