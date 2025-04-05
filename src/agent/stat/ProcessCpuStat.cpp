#include "ProcessCpuStat.h"
#include <iostream>
#include <fstream>
#include "../common.h"

ProcessCpuStat ProcessCpuStat::createFromProcProcessStatLine(const std::string &line)
{
    auto splitted = split(line, std::string(" "));

    ProcessCpuStat answer;

    int i = 0;

    answer.pid = GET_SPLIITED_INT(i); ++i;
    answer.name = splitted.at(i); ++i;
    answer.state = GET_SPLIITED_INT(i); ++i;
    answer.ppid = GET_SPLIITED_INT(i); ++i;
    answer.pgrp = GET_SPLIITED_INT(i); ++i;
    answer.session = GET_SPLIITED_INT(i); ++i;
    answer.tty_nr = GET_SPLIITED_INT(i); ++i;
    answer.tpgid = GET_SPLIITED_INT(i); ++i;
    answer.flags = GET_SPLIITED_INT(i); ++i;

    answer.minflt = GET_SPLIITED_INT(i); ++i;
    answer.cminflt = GET_SPLIITED_INT(i); ++i;
    answer.majflt = GET_SPLIITED_INT(i); ++i;
    answer.cmajflt = GET_SPLIITED_INT(i); ++i;
    answer.utime = GET_SPLIITED_INT(i); ++i;
    answer.stime = GET_SPLIITED_INT(i); ++i;
    answer.cutime = GET_SPLIITED_INT(i); ++i;
    answer.cstime = GET_SPLIITED_INT(i); ++i;
    answer.priority = GET_SPLIITED_INT(i); ++i;
    answer.nice = GET_SPLIITED_INT(i); ++i;
    answer.num_threads = GET_SPLIITED_INT(i); ++i;
    answer.itrealvalue = GET_SPLIITED_INT(i); ++i;
    answer.starttime = GET_SPLIITED_INT(i); ++i;
    answer.vsize = GET_SPLIITED_INT(i); ++i;
    answer.rss = GET_SPLIITED_INT(i); ++i;
    answer.rsslim = GET_SPLIITED_INT(i); ++i;
    answer.startcode = GET_SPLIITED_INT(i); ++i;
    answer.endcode = GET_SPLIITED_INT(i); ++i;
    answer.startstack = GET_SPLIITED_INT(i); ++i;
    answer.kstkesp = GET_SPLIITED_INT(i); ++i;
    answer.kstkeip = GET_SPLIITED_INT(i); ++i;
    answer.signal = GET_SPLIITED_INT(i); ++i;
    answer.blocked = GET_SPLIITED_INT(i); ++i;
    answer.sigignore = GET_SPLIITED_INT(i); ++i;
    answer.sigcatch = GET_SPLIITED_INT(i); ++i;
    answer.wchan = GET_SPLIITED_INT(i); ++i;
    answer.nswap = GET_SPLIITED_INT(i); ++i;
    answer.cnswap = GET_SPLIITED_INT(i); ++i;
    answer.exit_signal = GET_SPLIITED_INT(i); ++i;
    answer.processor = GET_SPLIITED_INT(i); ++i;
    answer.rt_priority = GET_SPLIITED_INT(i); ++i;
    answer.policy = GET_SPLIITED_INT(i); ++i;
    answer.delayacct_blkio_ticks = GET_SPLIITED_INT(i); ++i;
    answer.guest_time = GET_SPLIITED_INT(i); ++i;
    answer.cguest_time = GET_SPLIITED_INT(i); ++i;
    answer.start_data = GET_SPLIITED_INT(i); ++i;
    answer.end_data = GET_SPLIITED_INT(i); ++i;
    answer.start_brk = GET_SPLIITED_INT(i); ++i;
    answer.arg_start = GET_SPLIITED_INT(i); ++i;
    answer.arg_end = GET_SPLIITED_INT(i); ++i;
    answer.env_start = GET_SPLIITED_INT(i); ++i;
    answer.env_end = GET_SPLIITED_INT(i); ++i;
    answer.exit_code = GET_SPLIITED_INT(i); ++i;

    return answer;
}

ProcessCpuStat ProcessCpuStat::getProcessCpuStat(int pid)
{
    std::ifstream statFile("/proc/" + std::to_string(pid) + "/stat");

    std::string line;
    std::getline(statFile, line);

    if(line.empty()){
        return {};
    }

    auto answer = ProcessCpuStat::createFromProcProcessStatLine(line);

    statFile.close();

    return answer;
}

void ProcessCpuStat::print() const
{
    std::cout << "sources:" << std::endl;

    DEBUG_PRINT_SOURCE(pid);
    DEBUG_PRINT_SOURCE(name);
    DEBUG_PRINT_SOURCE(state);
    DEBUG_PRINT_SOURCE(ppid);
    DEBUG_PRINT_SOURCE(pgrp);
    DEBUG_PRINT_SOURCE(session);
    DEBUG_PRINT_SOURCE(tty_nr);
    DEBUG_PRINT_SOURCE(tpgid);
    DEBUG_PRINT_SOURCE(flags);

    DEBUG_PRINT_SOURCE(minflt);
    DEBUG_PRINT_SOURCE(cminflt);
    DEBUG_PRINT_SOURCE(majflt);
    DEBUG_PRINT_SOURCE(cmajflt);
    DEBUG_PRINT_SOURCE(utime);
    DEBUG_PRINT_SOURCE(stime);
    DEBUG_PRINT_SOURCE(cutime);
    DEBUG_PRINT_SOURCE(cstime);
    DEBUG_PRINT_SOURCE(priority);
    DEBUG_PRINT_SOURCE(nice);
    DEBUG_PRINT_SOURCE(num_threads);
    DEBUG_PRINT_SOURCE(itrealvalue);
    DEBUG_PRINT_SOURCE(starttime);
    DEBUG_PRINT_SOURCE(vsize);
    DEBUG_PRINT_SOURCE(rss);
    DEBUG_PRINT_SOURCE(rsslim);
    DEBUG_PRINT_SOURCE(startcode);
    DEBUG_PRINT_SOURCE(endcode);
    DEBUG_PRINT_SOURCE(startstack);
    DEBUG_PRINT_SOURCE(kstkesp);
    DEBUG_PRINT_SOURCE(kstkeip);
    DEBUG_PRINT_SOURCE(signal);
    DEBUG_PRINT_SOURCE(blocked);
    DEBUG_PRINT_SOURCE(sigignore);
    DEBUG_PRINT_SOURCE(sigcatch);
    DEBUG_PRINT_SOURCE(wchan);
    DEBUG_PRINT_SOURCE(nswap);
    DEBUG_PRINT_SOURCE(cnswap);
    DEBUG_PRINT_SOURCE(exit_signal);
    DEBUG_PRINT_SOURCE(processor);
    DEBUG_PRINT_SOURCE(rt_priority);
    DEBUG_PRINT_SOURCE(policy);
    DEBUG_PRINT_SOURCE(delayacct_blkio_ticks);
    DEBUG_PRINT_SOURCE(guest_time);
    DEBUG_PRINT_SOURCE(cguest_time);
    DEBUG_PRINT_SOURCE(start_data);
    DEBUG_PRINT_SOURCE(end_data);
    DEBUG_PRINT_SOURCE(start_brk);
    DEBUG_PRINT_SOURCE(arg_start);
    DEBUG_PRINT_SOURCE(arg_end);
    DEBUG_PRINT_SOURCE(env_start);
    DEBUG_PRINT_SOURCE(env_end);
    DEBUG_PRINT_SOURCE(exit_code);
}
