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
#include "../Model/SDVXSong.hpp"
#include "../Model/SDVXSongEntry.hpp"

class SDVXManager {
public:
    static const std::string& getDifficultyName(SDVXDifficulty difficulty, std::uint8_t infiniteVersion);

    std::vector<SDVXParsedSong> parseMusicDb(std::filesystem::path& musicDbPath, std::uint32_t releaseId);
    void addSong(SDVXParsedSong& song, std::uint32_t releaseId);
    void checkSongs(std::vector<SDVXParsedSong>& songs, std::uint32_t releaseId);
private:
    static inline constexpr std::string DIFFICULTY_NOVICE = "NOVICE";
    static inline constexpr std::string DIFFICULTY_ADVANCED = "ADVANCED";
    static inline constexpr std::string DIFFICULTY_EXHAUST = "EXHAUST";
    static inline constexpr std::string DIFFICULTY_MAXIMUM = "MAXIMUM";
    static inline constexpr std::string DIFFICULTY_INFINITE = "INFINITE";
    static inline constexpr std::string DIFFICULTY_GRAVITY = "GRAVITY";
    static inline constexpr std::string DIFFICULTY_HEAVENLY = "HEAVENLY";
    static inline constexpr std::string DIFFICULTY_VIVID = "VIVID";
    static inline constexpr std::string DIFFICULTY_EXCEED = "EXCEED";

    static SDVXDifficulty getDifficultyFromXml(std::string&& difficulty);
};

#endif //BEMANIMETADATAPARSER_SDVXMANAGER_HPP
