#include "SystemMemInfo.h"
#include <fstream>
#include <iostream>
#include "../common.h"

SystemMemInfo SystemMemInfo::getSystemMemInfo()
{
    SystemMemInfo answer;

    std::ifstream file("/proc/meminfo");

    std::string line;

    while(std::getline(file, line)){
        auto splitted = split(line, std::string(" "));
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

void SystemMemInfo::print()
{
    for(const auto& p  : data){
        std::cout << p.first << ": " << p.second << "\n";
    }
    std::cout << std::endl;
}
