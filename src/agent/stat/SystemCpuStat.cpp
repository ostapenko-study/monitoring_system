#include "SystemCpuStat.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "../common.h"

SystemCpuStat SystemCpuStat::createFromProcStatLine(const std::string &line)
{
    auto splitted = split(line, std::string(" "));

    SystemCpuStat result;
    result.name = splitted[0];

    int i = 1;
    result.user = GET_SPLIITED_INT(i); ++i;
    result.nice = GET_SPLIITED_INT(i); ++i;
    result.system = GET_SPLIITED_INT(i); ++i;
    result.idle = GET_SPLIITED_INT(i); ++i;
    result.iowait = GET_SPLIITED_INT(i); ++i;
    result.irq = GET_SPLIITED_INT(i); ++i;
    result.softirq = GET_SPLIITED_INT(i); ++i;
    result.steal = GET_SPLIITED_INT(i); ++i;
    result.guest = GET_SPLIITED_INT(i); ++i;
    result.guest_nice = GET_SPLIITED_INT(i); ++i;

    return result;
}

SystemCpuStat SystemCpuStat::getCurrentSystemCpuStat()
{
    std::ifstream statFile("/proc/stat");

    std::string line;
    std::getline(statFile, line);

    auto total_cpu_stat = SystemCpuStat::createFromProcStatLine(line);

    statFile.close();

    return total_cpu_stat;
}

std::vector<SystemCpuStat> SystemCpuStat::getCurrentAllCpuStat()
{
    std::vector<SystemCpuStat> answer;

    std::ifstream statFile("/proc/stat");

    std::string line;
    while(std::getline(statFile, line)){

        if(!line.size()){
            break;
        }

        if(line.substr(0, 3) == "cpu"){
            answer.push_back(createFromProcStatLine(line));
        }else{
            break;
        }
    }

    statFile.close();

    return answer;
}

void SystemCpuStat::print() const
{
    std::cout << "name: " << name << std::endl;

    std::cout << "sources:" << std::endl;

    DEBUG_PRINT_SOURCE(user)
    DEBUG_PRINT_SOURCE(nice)
    DEBUG_PRINT_SOURCE(system)
    DEBUG_PRINT_SOURCE(idle)
    DEBUG_PRINT_SOURCE(iowait)
    DEBUG_PRINT_SOURCE(irq)
    DEBUG_PRINT_SOURCE(softirq)
    DEBUG_PRINT_SOURCE(steal)
    DEBUG_PRINT_SOURCE(guest)
    DEBUG_PRINT_SOURCE(guest_nice)

    std::cout << "calculated:" << std::endl;

    DEBUG_PRINT_METHOD(totalCpuTime)
    DEBUG_PRINT_METHOD(idleCpuTimePercentage)
    DEBUG_PRINT_METHOD(usedCpuTimePercentage)
}
