//
// Created by Radio on 14/06/2024.
//

#ifndef BEMANIMETADATAPARSER_FILEUTIL_HPP
#define BEMANIMETADATAPARSER_FILEUTIL_HPP

#include <string>
#include <filesystem>

class FileUtil {
public:
    static std::string readFileIntoString(const std::filesystem::path& path);
};


#endif //BEMANIMETADATAPARSER_FILEUTIL_HPP
