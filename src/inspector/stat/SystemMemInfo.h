#ifndef SYSTEMMEMINFO_H
#define SYSTEMMEMINFO_H

#include <map>
#include <string>

struct SystemMemInfo
{
    std::map<std::string, long> data;

    static SystemMemInfo getSystemMemInfo();

    void print();
};


#endif // SYSTEMMEMINFO_H
