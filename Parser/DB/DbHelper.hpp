//
// Created by Radio on 10/05/2024.
//

#ifndef BEMANIMETADATAPARSER_DBHELPER_HPP
#define BEMANIMETADATAPARSER_DBHELPER_HPP

#include <SQLiteCpp/SQLiteCpp.h>

class DBHelper {
public:
    static const SQLite::Database& getDB();

private:
    static inline const SQLite::Database db = SQLite::Database(":memory:"); // NOLINT(*-interfaces-global-init)
};


#endif //BEMANIMETADATAPARSER_DBHELPER_HPP
