//
// Created by Radio on 26/05/2024.
//

#include "ReleaseService.hpp"
#include "DB/DbHelper.hpp"

void ReleaseService::addRelease(std::uint32_t gameId, std::string &&code) {
    auto& db = DBHelper::getDB();

    SQLite::Statement query(db, "INSERT INTO game_release (game_id, code) VALUES (?, ?)");

    query.bind(1, gameId);
    query.bind(2, code);
    query.exec();
    DBHelper::incrementUncommitedChanges();
}

std::vector<std::vector<std::string>> ReleaseService::getAllData() {
    auto& db = DBHelper::getDB();

    std::string sql = R"(
    SELECT
        `game_release`.*,
        `game`.`name` AS `game_name`
    FROM `game_release`
    JOIN `game` ON `game_release`.`game_id` = `game`.`id`
    )";

    SQLite::Statement query(db, sql);

    std::vector<std::vector<std::string>> data;

    while(query.executeStep()) {
        std::vector<std::string> row;
        // id
        row.push_back(query.getColumn(0).getString());
        // game_id + name
        row.push_back(query.getColumn(1).getString() + " - " + query.getColumn(3).getString());
        // code
        row.push_back(query.getColumn(2).getString());
        data.push_back(row);
    }

    return data;
}
