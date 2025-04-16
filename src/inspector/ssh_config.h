#pragma once

#include <QString>
#include <vector>

struct SshCredentials
{
    QString user;
    QString password;
    QString ip;

    QString host() const;
};

QString run_ssh(const SshCredentials& credentials, const QString& command);

std::string run_ssh_with_password(const std::string& userHost, const std::string& password, const std::vector<std::string>& remoteCommand);
