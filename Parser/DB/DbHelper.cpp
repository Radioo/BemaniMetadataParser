//
// Created by Radio on 10/05/2024.
//

#include "DbHelper.hpp"

const SQLite::Database& DBHelper::getDB() {
    return db;
}
