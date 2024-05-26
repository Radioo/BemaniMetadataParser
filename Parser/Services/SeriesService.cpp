//
// Created by Radio on 19/05/2024.
//

#include "SeriesService.hpp"
#include "DB/DbHelper.hpp"

void SeriesService::addSeries(std::string&& name) {
    auto& db = DBHelper::getDB();

    SQLite::Statement query(db, "INSERT INTO series (name) VALUES (?)");

    query.bind(1, name);
    query.exec();
    DBHelper::incrementUncommitedChanges();
}

std::vector<std::tuple<std::uint32_t, std::string>> SeriesService::getSeries() {
    auto& db = DBHelper::getDB();

    SQLite::Statement query(db, "SELECT * FROM series");
    std::vector<std::tuple<std::uint32_t, std::string>> series;

    while(query.executeStep()) {
        series.emplace_back(query.getColumn(0).getUInt(), query.getColumn(1).getString());
    }

    return series;
}
