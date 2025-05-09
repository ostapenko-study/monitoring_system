#include "ssh_config.h"
#include "qlist.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <pty.h>
#include <utmp.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <vector>
#include <poll.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <pty.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/wait.h>
#include <cstring>

QString SshCredentials::host() const
{
    return user + "@" + ip;
}

SshCredentials SshCredentials::fromJson(const QJsonObject &obj)
{
    SshCredentials answer;

    answer.user = obj.value("user").toString();
    answer.password = obj.value("password").toString();
    answer.ip = obj.value("ip").toString();

    return answer;
}

QString run_ssh(const SshCredentials &credentials, const QString &command)
{
    std::vector<std::string> __command;
    for (const QString& str : command.split(" ")) {
        __command.push_back(str.toStdString());
    }
    const auto [result, status] = run_ssh_with_password(credentials.host().toStdString(), credentials.password.toStdString(), __command);
    if(status){
        return QString::fromStdString(result);
    }else{
        throw std::runtime_error(result);
    }
}

std::pair<std::string, bool> run_ssh_with_password(const std::string &userHost, const std::string &password, const std::vector<std::string> &remoteCommand) {
    for(const auto& str: remoteCommand){
        std::cerr << str << " ";
    }
    std::cerr << std::endl;
    int master_fd;
    pid_t pid = forkpty(&master_fd, nullptr, nullptr, nullptr);

    if (pid == -1) {
        perror("forkpty");
        return {};
    }

    if (pid == 0) {
        // Дочірній процес: формуємо аргументи для execvp
        std::vector<std::string> args = { "ssh", userHost };
        args.insert(args.end(), remoteCommand.begin(), remoteCommand.end());

        std::vector<char*> argv;
        for (auto& arg : args)
            argv.push_back(const_cast<char*>(arg.c_str()));
        argv.push_back(nullptr); // null-terminate

        execvp("ssh", argv.data());
        perror("execvp failed");
        _exit(1);
    }

    // Батьківський процес: читаємо і реагуємо
    std::string buffer;
    char temp[256];
    bool passwordSent = false;

    while (true) {
        struct pollfd pfd = { master_fd, POLLIN, 0 };
        int ret = poll(&pfd, 1, 5000); // 5 сек таймаут

        if (ret > 0 && (pfd.revents & POLLIN)) {
            ssize_t len = read(master_fd, temp, sizeof(temp) - 1);
            if (len <= 0) break;
            temp[len] = '\0';
            std::cout << temp << std::flush;
            buffer += temp;

            if (!passwordSent && buffer.find("assword:") != std::string::npos) {
                std::string pwdWithNewline = password + "\n";
                write(master_fd, pwdWithNewline.c_str(), pwdWithNewline.size());
                passwordSent = true;
            }
        } else if (ret == 0) {
            std::cerr << "\n[!] Таймаут читання. Завершуємо дочірній процес.\n";

            kill(pid, SIGKILL);
            waitpid(pid, nullptr, 0);

            return {"[!] Таймаут читання. Завершуємо дочірній процес.", false};
        } else {
            perror("poll");
            break;
        }
    }

    int status;
    waitpid(pid, &status, 0);
    return {buffer, true};
}

std::string expand_path(const std::string& path) {
    if (!path.empty() && path[0] == '~') {
        const char* home = getenv("HOME");
        if (home) {
            return std::string(home) + path.substr(1);
        }
    }
    return path;
}

std::string run_scp_file_with_password(const std::string &source, const std::string &destination, const std::string &password) {
    int master_fd;
    pid_t pid = forkpty(&master_fd, nullptr, nullptr, nullptr);

    if (pid == -1) {
        perror("forkpty");
        return {};
    }

    if (pid == 0) {
        // Дочірній процес: викликаємо scp з розширеним шляхом
        std::string source_expanded = expand_path(source);
        std::string destination_expanded = destination; // можна теж розширити при потребі

        std::vector<std::string> args = { "scp", source_expanded, destination_expanded };

        std::vector<char*> argv;
        for (auto& arg : args)
            argv.push_back(const_cast<char*>(arg.c_str()));
        argv.push_back(nullptr);

        execvp("scp", argv.data());
        perror("execvp failed");
        _exit(1);
    }

    // Батьківський процес: читаємо вивід scp і при потребі вводимо пароль
    std::string buffer;
    char temp[256];
    bool passwordSent = false;

    while (true) {
        struct pollfd pfd = { master_fd, POLLIN, 0 };
        int ret = poll(&pfd, 1, 5000);

        if (ret > 0 && (pfd.revents & POLLIN)) {
            ssize_t len = read(master_fd, temp, sizeof(temp) - 1);
            if (len <= 0) break;
            temp[len] = '\0';
            std::cout << temp << std::flush;
            buffer += temp;

            if (!passwordSent && buffer.find("assword:") != std::string::npos) {
                std::string pwdWithNewline = password + "\n";
                write(master_fd, pwdWithNewline.c_str(), pwdWithNewline.size());
                passwordSent = true;
            }
        } else if (ret == 0) {
            std::cerr << "\n[!] Таймаут читання.\n";
            break;
        } else {
            perror("poll");
            break;
        }
    }

    int status;
    waitpid(pid, &status, 0);
    return buffer;
}

QString run_sсp_folder_from_local_to_remote(const SshCredentials &credentials, const std::string &source, const std::string &destination)
{
    run_ssh(credentials, "mkdir -p " + QString::fromStdString(destination));
    const QString tmp_archive = "tmp.tar";
    run_local_bash_command("tar -czf " + tmp_archive + " -C " + QString::fromStdString(source) + " .");
    run_scp_file_with_password(tmp_archive.toStdString(), credentials.host().toStdString() + ":" + destination, credentials.password.toStdString());
    run_ssh(credentials, "tar -xzf " + QString::fromStdString(destination) +  tmp_archive + " -C " + QString::fromStdString(destination));

    return {};
}

#include <QProcess>

void run_local_bash_command(const QString &command) {
    QProcess process;

    // Start a shell and run the command
    process.start("/bin/bash", QStringList() << "-c" << command);
    process.waitForFinished();

    // Read output
    QString output = process.readAllStandardOutput();
    QString errorOutput = process.readAllStandardError();

    qDebug() << "Output:" << output;
    if (!errorOutput.isEmpty())
        qDebug() << "Errors:" << errorOutput;
}
