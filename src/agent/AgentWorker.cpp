#include "AgentWorker.h"
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>
#include "process/PID_generator.h"
#include "stat/StatToJson.h"

AgentWorker::AgentWorker(QObject *parent)
    : QObject{parent}
{
    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &AgentWorker::onTic);
}

void AgentWorker::setConfig(AgentConfig config)
{
    m_config = config;
}

void AgentWorker::start()
{
    m_timer->start(m_config.timeout);
}

void AgentWorker::onTic()
{
    QJsonObject pkg;
    pkg.insert("system", generateSystemStat());

    {
        QJsonArray users;
        for(const auto& user: m_config.users){
            QJsonObject obj;
            obj.insert("user", QString::fromStdString(user));

            obj.insert("pids", generateProcessStat(pid_generator::findByUserName(user)));

            users.append(obj);
        }
        pkg.insert("users", users);
    }

    {
        QJsonArray processes;
        for(const auto& process: m_config.processes){
            QJsonObject obj;
            obj.insert("process", QString::fromStdString(process));

            obj.insert("pids", generateProcessStat(pid_generator::findByProcessName(process)));

            processes.append(obj);
        }
        pkg.insert("processes", processes);
    }

    emit packageCreated(pkg);
}

AgentWorker *createAgentWorker(const QString &config_filename)
{
    AgentWorker* answer;

    answer->setConfig(AgentConfig::generateFromFile(config_filename));

    return answer;
}
