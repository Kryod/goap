#pragma once

#include <string>
#include <vector>

class Utils {
public:
    static void listFiles(const std::string& directory,
                          const std::vector<std::string>& extensions,
                          std::vector<std::string>& resultPaths);
    static std::string toLower(const std::string& str);
    static std::string toUpper(const std::string& str);
};
