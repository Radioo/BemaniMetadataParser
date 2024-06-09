//
// Created by Radio on 09/06/2024.
//

#ifndef BEMANIMETADATAPARSER_DBUTIL_HPP
#define BEMANIMETADATAPARSER_DBUTIL_HPP

#include <SQLiteCpp/SQLiteCpp.h>

class DBUtil {
public:
    static SQLite::Database& getDb();
    static void initialize();
    static SQLite::Statement prepare(const std::string& query);
private:
    static inline SQLite::Database db = SQLite::Database(":memory:", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE); // NOLINT(*-interfaces-global-init)
};


#endif //BEMANIMETADATAPARSER_DBUTIL_HPP
