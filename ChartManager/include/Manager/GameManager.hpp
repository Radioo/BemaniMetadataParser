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
    GameManager();
private:
    std::unordered_map<std::uint32_t, Series> series;
    std::unordered_map<std::uint32_t, Game> games;
    std::unordered_map<std::uint32_t, Release> releases;

    void loadData();
};

#endif //BEMANIMETADATAPARSER_GAMEMANAGER_HPP
