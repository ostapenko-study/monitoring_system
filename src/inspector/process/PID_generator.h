#ifndef PID_GENERATOR_H
#define PID_GENERATOR_H

#include <vector>
#include <string>

namespace pid_generator{

std::vector<long> findByProcessName(const std::string& process_name);

std::vector<long> findByUserName(const std::string& user_name);

}

#endif // PID_GENERATOR_H
