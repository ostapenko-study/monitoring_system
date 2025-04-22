#pragma once

#include <string>
#include <vector>

#define GET_SPLIITED_INT(index) (index < splitted.size()) ? std::atoi(splitted[index].c_str()) : 0

#define DEBUG_PRINT_SOURCE(field_name) std::cout << #field_name << ": " << field_name << std::endl;
#define DEBUG_PRINT_METHOD(method_name) std::cout << #method_name << ": " << method_name() << std::endl;


//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split(std::string s, const std::string& delimiter);

#include <QString>

bool ensureDirectoryExists(const QString &path);

