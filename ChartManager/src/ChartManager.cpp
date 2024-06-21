//
// Created by Radio on 07/06/2024.
//

#include <utility>
#include <filesystem>

#include "../include/ChartManager.hpp"
#include "Util/DbUtil.hpp"

ChartManager::ChartManager(ChartManagerConfig config) : config(std::move(config)), gameManager(config.seriesCsvPath), sdvxManager() {
    DBUtil::initialize();

    if(!std::filesystem::exists("data")) {
        std::filesystem::create_directory("data");
    }
}

GameManager& ChartManager::getGameManager() {
    return this->gameManager;
}

SDVXManager& ChartManager::getSDVXManager() {
    return this->sdvxManager;
}

void ChartManager::commit() {
    DBUtil::commit();
}
