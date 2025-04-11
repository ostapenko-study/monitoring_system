#include "inspector_common.h"

std::vector<std::string> split(std::string s, const std::string &delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    size_t delimiter_length = delimiter.length();
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(!token.empty()){
            tokens.push_back(token);
        }
        s.erase(0, pos + delimiter_length);
    }
    tokens.push_back(s);

    return tokens;
}
