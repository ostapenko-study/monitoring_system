#include "StatToJson.h"

#include <QJsonValue>
#include <QJsonArray>

#include "SystemCpuStat.h"
#include "SystemMemInfo.h"

QJsonObject generateSystemStat()
{
    QJsonObject answer;

    {
        QJsonObject cpu_obj;

        const auto cpu_stat = SystemCpuStat::getCurrentSystemCpuStat();
#define WRITE_CPU_STAT(field) cpu_obj.insert(#field, qint64(cpu_stat.field));
        WRITE_CPU_STAT(user)
        WRITE_CPU_STAT(nice)
        WRITE_CPU_STAT(system)
        WRITE_CPU_STAT(idle)
        WRITE_CPU_STAT(iowait)
        WRITE_CPU_STAT(irq)
        WRITE_CPU_STAT(softirq)
        WRITE_CPU_STAT(steal)
        WRITE_CPU_STAT(guest)
        WRITE_CPU_STAT(guest_nice)
#undef WRITE_CPU_STAT
        answer.insert("cpu", cpu_obj);
    }

    {
        QJsonObject mem_obj;

        const auto mem_stat = SystemMemInfo::getSystemMemInfo();

        for(const auto& key : std::vector<std::string>{
                 "MemTotal",
                 "MemFree",
                 "MemAvailable",
                 "Buffers",
                 "Cached",
                 "SwapCached",
                 "SwapTotal",
                 "SwapFree",
                 "VmallocTotal",
                 "VmallocUsed",
                 "VmallocUsed",
                 "Percpu",
             }){
            mem_obj.insert(QString::fromStdString(key), qint64(mem_stat.data.at(key)));
        }

        answer.insert("mem", mem_obj);
    }

    return answer;

}

#include "ProcessCpuStat.h"
#include "ProcessMemStat.h"

QJsonObject generateProcessStat(const long pid)
{
    QJsonObject answer;

    answer.insert("pid", qint64(pid));

    {
        const auto cpu_stat = ProcessCpuStat::getProcessCpuStat(pid);
        answer.insert("name", QString::fromStdString(cpu_stat.name));
        answer.insert("state", QString::fromStdString(cpu_stat.state));
        answer.insert("ppid", qint64(cpu_stat.ppid));


        QJsonObject cpu_obj;
        {
#define WRITE_CPU_STAT(field) cpu_obj.insert(#field, qint64(cpu_stat.field));
            WRITE_CPU_STAT(utime)
            WRITE_CPU_STAT(stime)
            WRITE_CPU_STAT(cutime)
            WRITE_CPU_STAT(cstime)
            WRITE_CPU_STAT(nice)
            WRITE_CPU_STAT(guest_time)
            WRITE_CPU_STAT(cguest_time)
#undef WRITE_CPU_STAT
        }
        answer.insert("cpu", cpu_obj);

    }


    {
        const auto mem_stat = ProcessMemStat::getProcessMemStat(pid);

        QJsonObject mem_obj;
        for(const auto& [key, value] : mem_stat.data){
            if(!(key.substr(0, 2) == "Vm" || key.substr(0, 3) == "Rss")){
                continue;
            }
            mem_obj.insert(QString::fromStdString(key), qint64(value));
        }
        answer.insert("mem", mem_obj);
    }

    return answer;
}


QJsonArray generateProcessStat(std::vector<long> pids)
{
    QJsonArray pid_arr;
    for(auto pid : pids){
        pid_arr.append(generateProcessStat(pid));
    }

    return pid_arr;
}
