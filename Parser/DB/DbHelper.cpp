//
// Created by Radio on 10/05/2024.
//

#include "DbHelper.hpp"

#include <filesystem>
#include <fstream>
#include <regex>

const SQLite::Database& DBHelper::getDB() {
    if(!initialized) {
        createTables();
    }

    if(currentTransaction == nullptr) {
        currentTransaction = new SQLite::Transaction(db);
    }

    return db;
}

void DBHelper::createTables() {
    if(!std::filesystem::exists("DDL.sql")) {
        throw std::runtime_error("DDL.sql not found");
    }

    std::string ddlScript;
    std::ifstream ddlFile("DDL.sql");

    ddlFile.seekg(0, std::ios::end);
    ddlScript.reserve(ddlFile.tellg());
    ddlFile.seekg(0, std::ios::beg);

    ddlScript.assign((std::istreambuf_iterator<char>(ddlFile)), std::istreambuf_iterator<char>());

    ddlFile.close();

    db.exec(ddlScript);
    initialized = true;
}

void DBHelper::commit() {
    if(currentTransaction != nullptr) {
        currentTransaction->commit();
        delete currentTransaction;
        currentTransaction = nullptr;
    }

    dumpTable("series");

    uncommitedChanges = 0;
    if(afterCommitCallback != nullptr) {
        afterCommitCallback();
    }
    if(onUncommitedChangesChangeCallback != nullptr) {
        onUncommitedChangesChangeCallback();
    }
}

void DBHelper::dumpTable(const std::string& tableName) {
    // Get column names
    SQLite::Statement query(db, "PRAGMA table_info(" + tableName + ")");
    std::vector<std::string> columnNames;

    while(query.executeStep()) {
        columnNames.push_back(query.getColumn(1).getString());
    }

    // Dump data to CSV
    std::ofstream csvFile("./data/" + tableName + ".csv");

    auto columnCount = columnNames.size();
    for(int i = 0; i < columnCount; i++) {
        csvFile << columnNames[i];

        if(i < columnCount - 1) {
            csvFile << ",";
        }
    }

    csvFile << "\n";

    SQLite::Statement selectQuery(db, "SELECT * FROM " + tableName);

    while(selectQuery.executeStep()) {
        for(int i = 0; i < columnCount; i++) {
            std::string value = selectQuery.getColumn(i).getString();

            if(value.find(',') != std::string::npos) {
                csvFile << "\"" << value << "\"";
            } else {
                csvFile << value;
            }

            if(i < columnCount - 1) {
                csvFile << ",";
            }
        }

        csvFile << "\n";
    }

    csvFile.close();
}

void DBHelper::loadData() {
    // Disable foreign keys
    db.exec("PRAGMA foreign_keys=OFF");

    // Get all tables
    SQLite::Statement query(db, "SELECT name FROM sqlite_master WHERE type='table'");
    std::vector<std::string> tables;

    while(query.executeStep()) {
        tables.push_back(query.getColumn(0).getString());
    }

    // Load data from CSV
    for(const auto& table : tables) {
        std::filesystem::path csvPath("./data/" + table + ".csv");

        if(!std::filesystem::exists(csvPath)) {
            continue;
        }

        std::ifstream csvFile(csvPath);
        std::string line;

        // Get column names and count from database
        SQLite::Statement columnQuery(db, "PRAGMA table_info(" + table + ")");
        std::string columnNames;
        int columnCount = 0;
        while(columnQuery.executeStep()) {
            if (!columnNames.empty()) {
                columnNames += ",";
            }
            columnNames += columnQuery.getColumn(1).getString();
            columnCount++;
        }

        // Generate placeholders for VALUES
        std::string placeholders = std::string(columnCount * 2 - 1, '?');
        for (int i = 1; i < placeholders.size(); i += 2) {
            placeholders[i] = ',';
        }

        // Skip header in CSV file
        std::getline(csvFile, line);

        // Insert data
        while(std::getline(csvFile, line)) {
            // Create SQL statement
            std::string queryStr = "INSERT INTO ";
            queryStr += table;
            queryStr += " (";
            queryStr += columnNames;
            queryStr += ") VALUES(";
            queryStr += placeholders;
            queryStr += ")";
            SQLite::Statement insertQuery(db, queryStr);

            int i = 0;
            std::regex csvPattern(R"((\".*?\"|[^,]*)(,|$))");
            std::smatch csvMatch;

            while (std::regex_search(line, csvMatch, csvPattern)) {
                std::string cell = csvMatch[1].str();
                if (cell[0] == '"' && cell[cell.size() - 1] == '"') {
                    // Remove quotes if the cell is quoted
                    cell = cell.substr(1, cell.size() - 2);
                }
                insertQuery.bind(i + 1, cell);
                i++;
                line = csvMatch.suffix().str();

                if (line.empty()) {
                    break;
                }
            }

            insertQuery.exec();
        }

        csvFile.close();
    }

    // Enable foreign keys
    db.exec("PRAGMA foreign_keys=ON");
}

void DBHelper::incrementUncommitedChanges() {
    uncommitedChanges++;
    if(onUncommitedChangesChangeCallback != nullptr) {
        onUncommitedChangesChangeCallback();
    }
}

std::uint64_t DBHelper::getUncommitedChanges() {
    return uncommitedChanges;
}
