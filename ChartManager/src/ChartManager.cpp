//
// Created by Radio on 07/06/2024.
//

#include <utility>

#include "../include/ChartManager.hpp"
#include "Util/DbUtil.hpp"

ChartManager::ChartManager(ChartManagerConfig config) : config(std::move(config)), gameManager(config.seriesCsvPath){
    DBUtil::initialize();
}

GameManager& ChartManager::getGameManager() {
    return this->gameManager;
}
