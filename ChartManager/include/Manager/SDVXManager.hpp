//
// Created by Radio on 07/06/2024.
//

#ifndef BEMANIMETADATAPARSER_SDVXMANAGER_HPP
#define BEMANIMETADATAPARSER_SDVXMANAGER_HPP

#include <unordered_map>
#include <string>
#include <filesystem>
#include <vector>

#include "../Enum/SDVXDifficulty.hpp"
#include "../Model/SDVXParsedSong.hpp"

class SDVXManager {
public:
    std::vector<SDVXParsedSong> parseMusicDb(std::filesystem::path& musicDbPath);
private:
    static SDVXDifficulty getDifficultyFromXml(std::string&& difficulty);
};

#endif //BEMANIMETADATAPARSER_SDVXMANAGER_HPP
