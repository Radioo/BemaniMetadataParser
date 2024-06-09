//
// Created by Radio on 07/06/2024.
//

#ifndef BEMANIMETADATAPARSER_GAMEMANAGER_HPP
#define BEMANIMETADATAPARSER_GAMEMANAGER_HPP

#include <unordered_map>
#include <cstdint>

#include "Model/Series.hpp"
#include "Model/Game.hpp"
#include "Model/Release.hpp"

class GameManager {
public:
    explicit GameManager(std::filesystem::path& seriesCsvPath);
    void addSeries(std::string&& name);
    std::vector<Series> getSeries();
private:
    std::filesystem::path& seriesCsvPath;

    void loadData();
};

#endif //BEMANIMETADATAPARSER_GAMEMANAGER_HPP
