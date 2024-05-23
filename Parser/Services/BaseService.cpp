//
// Created by Radio on 23/05/2024.
//

#include "BaseService.hpp"
#include "DB/DbHelper.hpp"

std::vector<std::string> BaseService::getColumns() {
    auto& db = DBHelper::getDB();

    SQLite::Statement query(db, "PRAGMA table_info(" + getTableName() + ")");
    std::vector<std::string> columns;

    while(query.executeStep()) {
        columns.push_back(query.getColumn(1).getString());
    }

    return columns;
}

std::vector<std::vector<std::string>> BaseService::getAllData() {
    auto& db = DBHelper::getDB();

    SQLite::Statement query(db, "SELECT * FROM " + getTableName());
    std::vector<std::vector<std::string>> data;

    while(query.executeStep()) {
        std::vector<std::string> row;
        for(int i = 0; i < query.getColumnCount(); i++) {
            row.push_back(query.getColumn(i).getString());
        }
        data.push_back(row);
    }

    return data;
}
