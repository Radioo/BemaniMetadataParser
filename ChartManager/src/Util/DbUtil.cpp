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

        CREATE TABLE game (
            id INTEGER PRIMARY KEY,
            series_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            version INTEGER NOT NULL,
            FOREIGN KEY(series_id) REFERENCES series(id)
        );

        CREATE TABLE release (
            id INTEGER PRIMARY KEY,
            game_id INTEGER NOT NULL,
            code TEXT NOT NULL,
            FOREIGN KEY(game_id) REFERENCES game(id)
        );

        CREATE TABLE sdvx_song (
            id INTEGER PRIMARY KEY,
            release_id INTEGER NOT NULL,
            title TEXT NOT NULL,
            artist TEXT NOT NULL,
            FOREIGN KEY(release_id) REFERENCES release(id)
        );
    )");
}

SQLite::Statement DBUtil::prepare(const std::string& query) {
    return {db, query};
}
