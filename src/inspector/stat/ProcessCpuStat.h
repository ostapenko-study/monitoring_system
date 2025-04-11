#ifndef PROCESSCPUSTAT_H
#define PROCESSCPUSTAT_H

#include <string>

class ProcessCpuStat
{
public:
    int pid;
    std::string name;
    std::string state;
    int ppid;
    int pgrp;
    int session;
    int tty_nr;
    int tpgid;
    ulong flags;

    ulong minflt;
    ulong cminflt;
    ulong majflt;
    ulong cmajflt;
    ulong utime;
    ulong stime;
    ulong cutime;
    ulong cstime;
    ulong priority;
    ulong nice;
    ulong num_threads;
    ulong itrealvalue;
    ulong starttime;
    ulong vsize;
    ulong rss;
    ulong rsslim;
    ulong startcode;
    ulong endcode;
    ulong startstack;
    ulong kstkesp;
    ulong kstkeip;
    ulong signal;
    ulong blocked;
    ulong sigignore;
    ulong sigcatch;
    ulong wchan;
    ulong nswap;
    ulong cnswap;
    ulong exit_signal;
    ulong processor;
    ulong rt_priority;
    ulong policy;
    ulong delayacct_blkio_ticks;
    ulong guest_time;
    ulong cguest_time;
    ulong start_data;
    ulong end_data;
    ulong start_brk;
    ulong arg_start;
    ulong arg_end;
    ulong env_start;
    ulong env_end;
    ulong exit_code;

    static ProcessCpuStat createFromProcProcessStatLine(const std::string& line);

    static ProcessCpuStat getProcessCpuStat(int pid);

    void print() const;
};

#endif // PROCESSCPUSTAT_H
