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

    std::vector<Series> getSeries();
    Series getSeries(std::uint32_t id);
    void addSeries(std::string& name);
    void updateSeries(Series& series);
    void deleteSeries(std::uint32_t id);

    std::vector<Game> getGames();
    Game getGame(std::uint32_t id);
    void addGame(std::uint32_t seriesId, std::string& name, std::uint8_t version);
    void updateGame(Game& game);
    void deleteGame(std::uint32_t id);

    std::vector<Release> getReleases();
    Release getRelease(std::uint32_t id);
    void addRelease(std::uint32_t gameId, std::string& code);
    void updateRelease(Release& release);
    void deleteRelease(std::uint32_t id);
private:
    std::filesystem::path& seriesCsvPath;

    void loadData();
};

#endif //BEMANIMETADATAPARSER_GAMEMANAGER_HPP
