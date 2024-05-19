//
// Created by Radio on 10/05/2024.
//

#ifndef BEMANIMETADATAPARSER_DBHELPER_HPP
#define BEMANIMETADATAPARSER_DBHELPER_HPP

#include <SQLiteCpp/SQLiteCpp.h>
#include <optional>

class DBHelper {
public:
    static const SQLite::Database& getDB();
    static void commit();

private:
    static inline SQLite::Database db = SQLite::Database(":memory:", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); // NOLINT(*-interfaces-global-init)
    static inline SQLite::Transaction* currentTransaction = nullptr;

    static void createTables();
};


#endif //BEMANIMETADATAPARSER_DBHELPER_HPP
