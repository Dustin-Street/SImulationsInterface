#include "database.h"

#include <sqlite3.h>

#include <iostream>
#include <memory>
#include <utility>

namespace
{
using Database = std::unique_ptr<sqlite3, decltype(&sqlite3_close)>;
using Statement = std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)>;

Database openDatabase(const std::string &databasePath)
{
    sqlite3 *rawDatabase = nullptr;
    const int result = sqlite3_open(databasePath.c_str(), &rawDatabase);
    Database database(rawDatabase, sqlite3_close);

    if (result != SQLITE_OK)
    {
        std::cerr << "Could not open database: "
                  << (rawDatabase ? sqlite3_errmsg(rawDatabase) : "unknown SQLite error")
                  << '\n';
        return Database(nullptr, sqlite3_close);
    }

    return database;
}
}

bool initializeSimulationDatabase(const std::string &databasePath)
{
    Database database = openDatabase(databasePath);
    if (!database)
    {
        return false;
    }

    constexpr const char *createTableSql =
        "CREATE TABLE IF NOT EXISTS simulations ("
        "simulationID INTEGER PRIMARY KEY, "
        "simulationName TEXT NOT NULL, "
        "simulationLogic TEXT NOT NULL);";

    sqlite3_stmt *rawStatement = nullptr;
    int result = sqlite3_prepare_v2(database.get(), createTableSql, -1, &rawStatement, nullptr);
    Statement statement(rawStatement, sqlite3_finalize);
    if (result != SQLITE_OK)
    {
        std::cerr << "Could not prepare table creation: "
                  << sqlite3_errmsg(database.get()) << '\n';
        return false;
    }

    result = sqlite3_step(statement.get());
    if (result != SQLITE_DONE)
    {
        std::cerr << "Could not create simulations table: "
                  << sqlite3_errmsg(database.get()) << '\n';
        return false;
    }

    return true;
}

bool loadSimulationsFromDatabase(
    const std::string &databasePath,
    std::vector<SimulationRecord> &simulations)
{
    Database database = openDatabase(databasePath);
    if (!database)
    {
        return false;
    }

    constexpr const char *querySql =
        "SELECT simulationID, simulationName, simulationLogic "
        "FROM simulations ORDER BY simulationID;";

    sqlite3_stmt *rawStatement = nullptr;
    int result = sqlite3_prepare_v2(database.get(), querySql, -1, &rawStatement, nullptr);
    Statement statement(rawStatement, sqlite3_finalize);
    if (result != SQLITE_OK)
    {
        std::cerr << "Could not prepare simulations query: "
                  << sqlite3_errmsg(database.get()) << '\n';
        return false;
    }

    std::vector<SimulationRecord> loadedSimulations;
    while ((result = sqlite3_step(statement.get())) == SQLITE_ROW)
    {
        const auto *name = sqlite3_column_text(statement.get(), 1);
        const auto *logic = sqlite3_column_text(statement.get(), 2);
        const int nameLength = sqlite3_column_bytes(statement.get(), 1);
        const int logicLength = sqlite3_column_bytes(statement.get(), 2);

        loadedSimulations.push_back({
            sqlite3_column_int(statement.get(), 0),
            name ? std::string(reinterpret_cast<const char *>(name), nameLength) : std::string{},
            logic ? std::string(reinterpret_cast<const char *>(logic), logicLength) : std::string{}});
    }

    if (result != SQLITE_DONE)
    {
        std::cerr << "Could not read simulations: "
                  << sqlite3_errmsg(database.get()) << '\n';
        return false;
    }

    simulations = std::move(loadedSimulations);
    return true;
}
