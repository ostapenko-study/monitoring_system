#ifndef SYSTEMCPUSTAT_H
#define SYSTEMCPUSTAT_H

#include <string>
#include <vector>

//https://support.checkpoint.com/results/sk/sk65143
struct SystemCpuStat
{
    std::string name; //name of cpu

    int user; //normal processes executing in user mode
    int nice; //niced processes executing in user mode
    int system; //processes executing in kernel mode
    int idle; //twiddling thumbs
    int iowait; //waiting for I/O to complete
    int irq; //servicing interrupts
    int softirq; //servicing softirqs
    int steal; //counts the ticks spent executing other virtual hosts (in virtualised environments like Xen)
    int guest; //counts the time spent running a virtual CPU for guest operating systems under the control of the Linux kernel
    int guest_nice; //Time spent running a niced guest (virtual CPU for guest operating systems under the control of the Linux kernel).

    int totalCpuTime() const //this will yield 100% of CPU time
    {
        return user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
    }

    float idleCpuTimePercentage() const
    {
        return idle * 100.F / totalCpuTime();
    }

    float usedCpuTimePercentage() const
    {
        return 100.F - idleCpuTimePercentage();
    }

    static SystemCpuStat createFromProcStatLine(const std::string& line);

    static SystemCpuStat getCurrentSystemCpuStat();

    static std::vector<SystemCpuStat> getCurrentAllCpuStat();

    void print() const;
};

#endif // SYSTEMCPUSTAT_H
