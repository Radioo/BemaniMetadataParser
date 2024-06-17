//
// Created by Radio on 14/06/2024.
//

#include <fstream>

#include "FileUtil.hpp"

std::string FileUtil::readFileIntoString(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}
