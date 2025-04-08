#include "AgentWorker.h"
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>
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
    pkg.insert("users", generateProcessStatByUsers(m_config.users));
    pkg.insert("processes", generateProcessStatByNames(m_config.processes));

    emit packageCreated(pkg);
}

AgentWorker *createAgentWorker(const QString &config_filename)
{
    AgentWorker* answer = new AgentWorker;

    answer->setConfig(AgentConfig::generateFromFile(config_filename));

    return answer;
}
