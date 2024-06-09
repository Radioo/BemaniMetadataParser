//
// Created by Radio on 07/06/2024.
//

#include <csv.hpp>
#include <filesystem>

#include "../include/Manager/GameManager.hpp"
#include "../Util/DbUtil.hpp"

GameManager::GameManager(std::filesystem::path& seriesCsvPath) : seriesCsvPath(seriesCsvPath) {
    this->loadData();
}

void GameManager::loadData() {
//    this->series = this->csvUtil.deserialize<Series>(this->seriesCsvPath);
}

void GameManager::addSeries(std::string&& name) {
    auto query = DBUtil::prepare("INSERT INTO series (name) VALUE (?)");
    query.bind(1, name);
    auto changes = query.exec();
    if(changes != 1) {
        throw std::runtime_error("Failed to insert series");
    }
}

std::vector<Series> GameManager::getSeries() {
    auto countQuery = DBUtil::prepare("SELECT COUNT(*) FROM series");
    countQuery.executeStep();
    auto count = countQuery.getColumn(0).getInt();

    auto seriesQuery = DBUtil::prepare("SELECT * FROM series");
    std::vector<Series> series(count);

    std::uint32_t i = 0;
    while(seriesQuery.executeStep()) {
        series[i++] = {
                seriesQuery.getColumn(0).getUInt(),
                seriesQuery.getColumn(1).getString()
        };
    }

    return series;
}
