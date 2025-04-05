#ifndef STATTOJSON_H
#define STATTOJSON_H

#include <QJsonObject>

QJsonObject generateSystemStat();
QJsonObject generateProcessStat(const long pid);
QJsonArray generateProcessStat(std::vector<long> pids);



#endif // STATTOJSON_H
