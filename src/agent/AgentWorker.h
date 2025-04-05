#ifndef AGENTWORKER_H
#define AGENTWORKER_H

#include <QObject>
#include "AgentConfig.h"

class QTimer;

class AgentWorker : public QObject
{
    Q_OBJECT
public:
    explicit AgentWorker(QObject *parent = nullptr);

    void setConfig(AgentConfig config);

    void start();

signals:
    void packageCreated(QJsonObject);
protected slots:
    void onTic();
protected:
    AgentConfig m_config;
    QTimer* m_timer;
};

AgentWorker* createAgentWorker(const QString& config_filename = AgentConfig::default_config_filename);

#endif // AGENTWORKER_H
