//
// Created by Radio on 07/06/2024.
//

#ifndef BEMANIMETADATAPARSER_CHARTMANAGER_HPP
#define BEMANIMETADATAPARSER_CHARTMANAGER_HPP


#include "Manager/GameManager.hpp"
#include "Manager/SDVXManager.hpp"
#include "ChartManagerConfig.hpp"

class ChartManager {
public:
    explicit ChartManager(ChartManagerConfig config);
    GameManager& getGameManager();
    SDVXManager& getSDVXManager();
private:
    ChartManagerConfig config;
    GameManager gameManager;
    SDVXManager sdvxManager;
};


#endif //BEMANIMETADATAPARSER_CHARTMANAGER_HPP
