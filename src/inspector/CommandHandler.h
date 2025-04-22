#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QJsonObject>

namespace command_handler
{

QJsonObject& appendIndex(QJsonObject& output, const QJsonObject& request);

QJsonObject getTopRequest(const QJsonObject& );
QJsonObject getScanNetworkRequest(const QJsonObject& );


QJsonObject getTopRequestBySsh(const QJsonObject& );

QJsonObject setupDeviceBySsh(const QJsonObject& , int port);

}

#endif // COMMANDHANDLER_H
