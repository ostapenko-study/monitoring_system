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

QString run_ssh(const SshCredentials &credentials, const QString &command)
{
    std::vector<std::string> __command;
    for (const QString& str : command.split(" ")) {
        __command.push_back(str.toStdString());
    }
    return QString::fromStdString(
                run_ssh_with_password(credentials.host().toStdString(), credentials.password.toStdString(), __command)
        );
}

std::string run_ssh_with_password(const std::string &userHost, const std::string &password, const std::vector<std::string> &remoteCommand) {
    std::cerr << userHost << password << std::endl;
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

