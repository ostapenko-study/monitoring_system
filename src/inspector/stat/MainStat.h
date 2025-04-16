#ifndef MAINSTAT_H
#define MAINSTAT_H

#include <QString>
#include <QJsonObject>
#include "ssh_config.h"

struct ProcessMainInfo{
    int pid = -1;
    QString user;
    double pr;
    double ni;
    double virt;
    double res;
    double shr;
    QString state;
    double cpuUsage;
    double memUsage;
    QString time;
    qint64 timeInSecs;
    QString command;

    QJsonObject toJson() const;

    static ProcessMainInfo fromTopLine(const QString& line);
    static ProcessMainInfo fromPsLine(const QString& line);
};

QVector<ProcessMainInfo> getProcessTopInfos();
QVector<ProcessMainInfo> getProcessTopInfosBySsh(const SshCredentials& ssh_credentials);
QVector<ProcessMainInfo> parseTopOutput(const QString& output);


QVector<ProcessMainInfo> getProcessPsInfos();
QVector<ProcessMainInfo> getProcessPsInfosBySsh(const SshCredentials& ssh_credentials);
QVector<ProcessMainInfo> parsePsOutput(const QString& output);


#endif // MAINSTAT_H
