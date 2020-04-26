#include <algorithm>

#include "cute_files.h"
#include "utils.h"

void Utils::listFiles(const std::string& directory,
                      const std::vector<std::string>& extensions,
                      std::vector<std::string>& resultPaths) {
    struct UserData {
        std::vector<std::string>* extensions;
        std::vector<std::string>* paths;
    };

    std::vector<std::string> exts = extensions;
    for (std::string& ext : exts) {
        ext = Utils::toLower(ext);
    }

    UserData userData;
    userData.extensions = &exts;
    userData.paths = &resultPaths;

    cf_traverse(
        directory.c_str(),
        [](cf_file_t* file, void* userData) {
            UserData* data = static_cast<UserData*>(userData);
            bool extensionAllowed =
                std::find(data->extensions->begin(), data->extensions->end(),
                          Utils::toLower(file->ext)) != data->extensions->end();
            if (file->is_reg && extensionAllowed) {
                data->paths->push_back(file->path);
            }
        },
        &userData);
}

std::string Utils::toLower(const std::string& str) {
    std::string result = str;
    std::transform(str.begin(), str.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string Utils::toUpper(const std::string& str) {
    std::string result = str;
    std::transform(str.begin(), str.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}
