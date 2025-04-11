#ifndef STATTOJSON_H
#define STATTOJSON_H

#include <QJsonObject>

QJsonObject generateSystemStat();
QJsonObject generateProcessStat(const long pid);
QJsonArray generateProcessStat(const std::vector<long>& pids);

QJsonArray generateProcessStatByUsers(const std::vector<std::string>& users);
QJsonArray generateProcessStatByNames(const std::vector<std::string>& names);


#endif // STATTOJSON_H
