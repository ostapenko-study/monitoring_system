#pragma once

#include <QString>
#include <vector>
#include <QJsonObject>

struct SshCredentials
{
    QString user;
    QString password;
    QString ip;

    QString host() const;

    static SshCredentials fromJson(const QJsonObject &obj);
};

QString run_ssh(const SshCredentials& credentials, const QString& command);
std::pair<std::string, bool> run_ssh_with_password(const std::string& userHost, const std::string& password, const std::vector<std::string>& remoteCommand);

QString run_sсp_folder_from_local_to_remote(const SshCredentials& credentials, const std::string &source, const std::string &destination);
std::string run_scp_file_with_password(const std::string &source, const std::string &destination, const std::string &password);

void run_local_bash_command(const QString &command);
