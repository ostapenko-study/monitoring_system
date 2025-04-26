#include "inspector_common.h"
#include <QDir>
#include <sstream>

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

bool ensureDirectoryExists(const QString &path) {
    QDir dir(path);
    if (!dir.exists()) {
        if (dir.mkpath(".")) {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}

std::string joinVector(const std::vector<std::string> &vec, const std::string &delimiter) {
    if (vec.empty()) return ""; // Якщо вектор порожній, повертаємо порожній рядок

    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) {
            oss << delimiter;  // Додаємо роздільник, але не в кінці
        }
    }

    return oss.str(); // Повертаємо склеєний рядок
}
