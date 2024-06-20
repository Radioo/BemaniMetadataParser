//
// Created by Radio on 07/06/2024.
//

#ifndef BEMANIMETADATAPARSER_GAMEMANAGER_HPP
#define BEMANIMETADATAPARSER_GAMEMANAGER_HPP

#include <unordered_map>
#include <cstdint>
#include <filesystem>
#include <vector>

#include "Model/Series.hpp"
#include "Model/Game.hpp"
#include "Model/Release.hpp"

class GameManager {
public:
    explicit GameManager(std::filesystem::path& seriesCsvPath);
    void addSeries(std::string&& name);
    std::vector<Series> getSeries();
    void addGame(std::uint32_t seriesId, std::string&& name, std::uint8_t version);
    std::vector<Game> getGames();
    void addRelease(std::uint32_t gameId, std::string&& code);
    std::vector<Release> getReleases();
private:
    std::filesystem::path& seriesCsvPath;

    void loadData();
};

#endif //BEMANIMETADATAPARSER_GAMEMANAGER_HPP
