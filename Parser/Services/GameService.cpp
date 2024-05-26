//
// Created by Radio on 26/05/2024.
//

#include "GameService.hpp"
#include "DB/DbHelper.hpp"

void GameService::addGame(std::uint32_t seriesId, std::string &&name, std::uint32_t version) {
    auto& db = DBHelper::getDB();

    SQLite::Statement query(db, "INSERT INTO game (series_id, name, version) VALUES (?, ?, ?)");

    query.bind(1, seriesId);
    query.bind(2, name);
    query.bind(3, version);
    query.exec();
    DBHelper::incrementUncommitedChanges();
}

std::vector<std::vector<std::string>> GameService::getAllData() {
    auto& db = DBHelper::getDB();

    std::string sql = R"(
    SELECT
        `game`.*,
        `series`.`name` AS `series_name`
    FROM `game`
    JOIN `series` ON `game`.`series_id` = `series`.`id`
    )";

    SQLite::Statement query(db, sql);

    std::vector<std::vector<std::string>> data;

    while(query.executeStep()) {
        std::vector<std::string> row;
        // id
        row.push_back(query.getColumn(0).getString());
        // series_id + name
        row.push_back(query.getColumn(1).getString() + " - " + query.getColumn(4).getString());
        // name
        row.push_back(query.getColumn(2).getString());
        // version
        row.push_back(query.getColumn(3).getString());
        data.push_back(row);
    }

    return data;
}
