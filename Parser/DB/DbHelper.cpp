//
// Created by Radio on 10/05/2024.
//

#include "DbHelper.hpp"

#include <filesystem>
#include <fstream>

const SQLite::Database& DBHelper::getDB() {
    createTables();

    if(currentTransaction == nullptr) {
        SQLite::Transaction transaction(db);
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
}

void DBHelper::commit() {
    if(currentTransaction != nullptr) {
        currentTransaction->commit();
        delete currentTransaction;
        currentTransaction = nullptr;
    }
}
