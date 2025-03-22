/*
* File: SQLiteConnection.h
* Author: trung.la
* Date: 03-22-2025
* Description: This file contains the declarations for SQLite connection
*/

#ifndef COMMON_DATABASE_SQLITECONNECTION_H_
#define COMMON_DATABASE_SQLITECONNECTION_H_

#include "common/database/IDatabaseConnection.h"

class SQLiteConnection : public IDatabaseConnection
{
public:
    using SQLiteDatabaseUPtr = std::unique_ptr<SQLite::Database>;
    SQLiteConnection() = delete;
    SQLiteConnection(const std::string &dbPath);

    ~SQLiteConnection() override = default;

    void query(const std::string &query) override;
    void transaction(const std::string &query) override;
    SQLite::Database *connection() override;

private:
    SQLiteDatabaseUPtr m_db;
    std::string m_dbPath; 
};

#endif // COMMON_DATABASE_SQLITECONNECTION_H_