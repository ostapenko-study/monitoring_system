#ifndef AGENTCONFIG_H
#define AGENTCONFIG_H

#include <vector>
#include <string>

#include <QJsonObject>

struct AgentConfig{
    std::vector<std::string> users;
    std::vector<std::string> processes;

    int timeout;

    static AgentConfig createFromJson(const QJsonObject& );
    QJsonObject toJson() const;

    static const QString default_config_filename;

    static AgentConfig generateFromFile(const QString& config_filename = default_config_filename);
    void saveToFile(const QString& config_filename = default_config_filename) const;
};

#endif // AGENTCONFIG_H
