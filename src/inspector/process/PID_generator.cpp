#include "PID_generator.h"
#include <QProcess>
#include <QDebug>

namespace {

    std::vector<long> parseReadAllStandardOutputPsCommand(const QString& data, QString ban = "")
    {
        std::vector<long> answer;

        foreach (const auto& line, data.split('\n')) {
            if(line.contains(ban) && !ban.isEmpty()){
                continue;
            }
            auto pid = QString(line).simplified().split(" ").at(0).toInt();
            if(pid == 0){
                continue;
            }
            answer.push_back(pid);
        };

        return answer;
    }
}

std::vector<long> pid_generator::findByProcessName(const std::string& process_name)
{
    QProcess process;
    const auto command = QString("ps -ax | grep %1").arg(QString::fromStdString(process_name));
    process.start("bash", QStringList() << "-c" << command);
    process.waitForFinished();

    if(!process.readAllStandardError().isEmpty()){
        qWarning() << __FILE__ << ":" << __LINE__;
    }

    return parseReadAllStandardOutputPsCommand(process.readAllStandardOutput(), "grep");
}

std::vector<long> pid_generator::findByUserName(const std::string& user_name)
{
    std::vector<long> answer;

    QProcess process;
    const auto command = QString("ps -u %1").arg(QString::fromStdString(user_name));
    process.start("bash", QStringList() << "-c" << command);
    process.waitForFinished();

    return parseReadAllStandardOutputPsCommand(process.readAllStandardOutput(), "grep");
}
