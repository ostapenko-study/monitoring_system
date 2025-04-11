#include "ProcessMemStat.h"
#include <fstream>
#include <iostream>
#include "inspector_common.h"

ProcessMemStat ProcessMemStat::getProcessMemStat(long pid)
{
    ProcessMemStat answer;

    std::ifstream file("/proc/" + std::to_string(pid) + "/status");

    std::string line;

    while(std::getline(file, line)){
        auto splitted = split(line, std::string("\t"));
        if(splitted.size() < 2){
            std::cerr << "loggic_error";
            continue;
        }
        splitted.at(0).pop_back(); //remove ':'
        answer.data[splitted.at(0)] = std::atoi(splitted.at(1).c_str());
    }

    file.close();

    return answer;
}

void ProcessMemStat::print() const
{
    for(const auto& p  : data){
        std::cout << p.first << ": " << p.second << "\n";
    }
    std::cout << std::endl;
}
