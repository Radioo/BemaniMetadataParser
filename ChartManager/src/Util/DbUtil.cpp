//
// Created by Radio on 09/06/2024.
//

#include "DbUtil.hpp"

SQLite::Database& DBUtil::getDb() {
    return db;
}

void DBUtil::initialize() {
    db.exec(R"(
        CREATE TABLE series (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL
        );
    )");
}

SQLite::Statement DBUtil::prepare(const std::string& query) {
    return {db, query};
}
