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
}
