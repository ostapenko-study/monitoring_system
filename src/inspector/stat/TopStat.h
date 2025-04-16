#ifndef TOPSTAT_H
#define TOPSTAT_H

#include <QString>
#include <QJsonObject>
#include "ssh_config.h"


struct ProcessTopInfo{
    int pid = -1;
    QString user;
    double pr;
    double ni;
    double virt;
    double res;
    double shr;
    char state;
    double cpuUsage;
    double memUsage;
    QString time;
    qint64 timeInSecs;
    QString command;

    QJsonObject toJson() const;

    static ProcessTopInfo fromTopLine(const QString& line);
};

QVector<ProcessTopInfo> getProcessTopInfos();
QVector<ProcessTopInfo> getProcessTopInfosBySsh(const SshCredentials& ssh_credentials);
QVector<ProcessTopInfo> parseTopOutput(const QString& output);

#endif // TOPSTAT_H
