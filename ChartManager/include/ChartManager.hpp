//
// Created by Radio on 07/06/2024.
//

#ifndef BEMANIMETADATAPARSER_CHARTMANAGER_HPP
#define BEMANIMETADATAPARSER_CHARTMANAGER_HPP


#include "Manager/GameManager.hpp"
#include "ChartManagerConfig.hpp"

class ChartManager {
public:
    explicit ChartManager(ChartManagerConfig config);
    GameManager& getGameManager();
private:
    ChartManagerConfig config;
    GameManager gameManager;
};


#endif //BEMANIMETADATAPARSER_CHARTMANAGER_HPP
