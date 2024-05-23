//
// Created by Radio on 10/05/2024.
//

#ifndef BEMANIMETADATAPARSER_DBHELPER_HPP
#define BEMANIMETADATAPARSER_DBHELPER_HPP

#include <SQLiteCpp/SQLiteCpp.h>
#include <optional>
#include <functional>

class DBHelper {
public:
    static inline std::function<void()> afterCommitCallback = nullptr;
    static inline std::function<void()> onUncommitedChangesChangeCallback = nullptr;

    static const SQLite::Database& getDB();
    static void commit();
    static void loadData();
    static void incrementUncommitedChanges();
    static std::uint64_t getUncommitedChanges();

private:
    static inline std::uint64_t uncommitedChanges = 0;
    static inline SQLite::Database db = SQLite::Database(":memory:", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE); // NOLINT(*-interfaces-global-init)
    static inline bool initialized = false;
    static inline SQLite::Transaction* currentTransaction = nullptr;

    static void createTables();
    static void dumpTable(const std::string& tableName);
};


#endif //BEMANIMETADATAPARSER_DBHELPER_HPP
