#ifndef PROCESSMEMSTAT_H
#define PROCESSMEMSTAT_H

#include <map>
#include <string>


struct ProcessMemStat
{
    std::map<std::string, long> data;

    static ProcessMemStat getProcessMemStat(long pid);

    void print() const;
};

#endif // PROCESSMEMSTAT_H
