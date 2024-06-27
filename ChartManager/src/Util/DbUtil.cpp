//
// Created by Radio on 09/06/2024.
//

#include <iostream>
#include <csv.hpp>

#include "DbUtil.hpp"

SQLite::Database& DBUtil::getDb() {
    return db;
}

void DBUtil::initialize() {
    db.exec(R"(
        PRAGMA foreign_keys = ON;

        CREATE TABLE series (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL
        );

        CREATE UNIQUE INDEX series_name_index ON series(name);

        CREATE TABLE game (
            id INTEGER PRIMARY KEY,
            series_id INTEGER NOT NULL,
            name TEXT NOT NULL,
            version INTEGER NOT NULL,
            FOREIGN KEY(series_id) REFERENCES series(id) ON DELETE CASCADE ON UPDATE CASCADE
        );

        CREATE UNIQUE INDEX game_series_id_version_index ON game(series_id, version);

        CREATE TABLE release (
            id INTEGER PRIMARY KEY,
            game_id INTEGER NOT NULL,
            code TEXT NOT NULL,
            FOREIGN KEY(game_id) REFERENCES game(id) ON DELETE CASCADE ON UPDATE CASCADE
        );

        CREATE TABLE sdvx_song (
            id INTEGER PRIMARY KEY,
            title TEXT NOT NULL,
            artist TEXT NOT NULL
        );

        CREATE TABLE sdvx_song_entry (
            id INTEGER PRIMARY KEY,
            sdvx_song_id INTEGER NOT NULL,
            internal_id INTEGER NOT NULL,
            infinite_version INTEGER,
            FOREIGN KEY(sdvx_song_id) REFERENCES sdvx_song(id) ON DELETE CASCADE ON UPDATE CASCADE
        );

        CREATE TABLE sdvx_chart (
            id INTEGER PRIMARY KEY,
            sdvx_song_id INTEGER NOT NULL,
            FOREIGN KEY(sdvx_song_id) REFERENCES sdvx_song(id) ON DELETE CASCADE ON UPDATE CASCADE
        );

        CREATE TABLE sdvx_chart_entry (
            id INTEGER PRIMARY KEY,
            sdvx_chart_id INTEGER NOT NULL,
            difficulty INTEGER NOT NULL,
            level INTEGER NOT NULL,
            limited INTEGER,
            max_ex_score INTEGER,
            FOREIGN KEY(sdvx_chart_id) REFERENCES sdvx_chart(id) ON DELETE CASCADE ON UPDATE CASCADE
        );

        CREATE TABLE sdvx_song_entry_release (
            release_id INTEGER NOT NULL,
            sdvx_song_entry_id INTEGER NOT NULL,
            PRIMARY KEY(release_id, sdvx_song_entry_id),
            FOREIGN KEY(release_id) REFERENCES release(id) ON DELETE CASCADE ON UPDATE CASCADE,
            FOREIGN KEY(sdvx_song_entry_id) REFERENCES sdvx_song_entry(id) ON DELETE CASCADE ON UPDATE CASCADE
        );

        CREATE TABLE sdvx_chart_entry_release (
            release_id INTEGER NOT NULL,
            sdvx_chart_entry_id INTEGER NOT NULL,
            PRIMARY KEY(release_id, sdvx_chart_entry_id),
            FOREIGN KEY(release_id) REFERENCES release(id) ON DELETE CASCADE ON UPDATE CASCADE,
            FOREIGN KEY(sdvx_chart_entry_id) REFERENCES sdvx_chart_entry(id) ON DELETE CASCADE ON UPDATE CASCADE
        );
    )");

    load();
}

SQLite::Statement DBUtil::prepare(const std::string& query) {
    return {db, query};
}

void DBUtil::commit() {
    auto tablesQuery = prepare("SELECT name FROM sqlite_master WHERE type='table';");
    while(tablesQuery.executeStep()) {
        auto tableName = tablesQuery.getColumn(0).getString();

        auto columnsQuery = prepare("PRAGMA table_info(" + tableName + ");");
        std::vector<std::string> columns;

        while(columnsQuery.executeStep()) {
            columns.push_back(columnsQuery.getColumn(1).getString());
        }

        auto dataQuery = prepare("SELECT * FROM " + tableName + ";");
        auto columnCount = columns.size();

        std::ofstream file("data/" + tableName + ".csv");
        auto writer = csv::make_csv_writer(file);

        writer << columns;

        while(dataQuery.executeStep()) {
            std::vector<std::string> row(columnCount);
            for(auto i = 0; i < columnCount; i++) {
                row[i] = dataQuery.getColumn(i).getString();
            }

            writer << row;
        }

        file.close();
    }
}

void DBUtil::load() {
    auto tablesQuery = prepare("SELECT name FROM sqlite_master WHERE type='table';");
    while(tablesQuery.executeStep()) {
        auto tableName = tablesQuery.getColumn(0).getString();
        auto filePath = "data/" + tableName + ".csv";

        if(!std::filesystem::exists(filePath)) {
            continue;
        }

        auto columnsQuery = prepare("PRAGMA table_info(" + tableName + ");");
        std::vector<std::string> columns;

        while(columnsQuery.executeStep()) {
            columns.push_back(columnsQuery.getColumn(1).getString());
        }

        auto columnCount = columns.size();

        std::string insertQuery = "INSERT INTO " + tableName + " (";
        for(auto i = 0; i < columnCount; i++) {
            insertQuery += columns[i];
            if(i != columnCount - 1) {
                insertQuery += ", ";
            }
        }
        insertQuery += ") VALUES (";
        for(auto i = 0; i < columnCount; i++) {
            insertQuery += "?";
            if(i != columnCount - 1) {
                insertQuery += ", ";
            }
        }
        insertQuery += ");";

        csv::CSVReader reader(filePath);
        for(auto& row : reader) {
            auto query = prepare(insertQuery);
            for(auto i = 0; i < columnCount; i++) {
                query.bind(i + 1, row[i].get<std::string>());
            }

            query.exec();
            query.reset();
        }
    }
}