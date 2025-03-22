/*
* File: SQLiteUserRepository.cpp
* Author: trung.la
* Date: 03-22-2025
* Description: This file contains the definitions of the SQLiteUserRepository class.
*/

#include "services/user/repositories/SQLiteUserRepository.h"

SQLiteUserRepository::SQLiteUserRepository(const std::shared_ptr<IDatabaseConnection> &connection)
    : m_connection(connection)
{
}

void SQLiteUserRepository::createTable()
{
    auto const connection = m_connection.lock();
    if (!connection)
    {
        return;
    }

    const std::string sql = 
            "CREATE TABLE IF NOT EXISTS Users ("
            "user_id TEXT PRIMARY KEY, "
            "email TEXT UNIQUE, "
            "username TEXT UNIQUE NOT NULL, "
            "created_at TEXT DEFAULT CURRENT_TIMESTAMP, "
            "updated_at TEXT DEFAULT CURRENT_TIMESTAMP"
            ")";

    connection->transaction(sql);
}

void SQLiteUserRepository::insert(const User &user)
{
    const std::string sql =
            "INSERT INTO Users (user_id, email, username, created_at, updated_at) "
            "VALUES ('" + user.getUserId() + "', '" + user.getEmail() + "', '"
            + user.getUserName() + "', '" + user.getCreateAt() + "', '"
            + user.getUpdateAt() + "')";
    
    auto const connection = m_connection.lock();
    if (!connection)
    {
        return;
    }

    connection->transaction(sql);
}

void SQLiteUserRepository::update(const User &user)
{
}

void SQLiteUserRepository::remove(const User &user)
{
}

std::vector<User> SQLiteUserRepository::getAll()
{
    return std::vector<User>();
}

std::optional<User> SQLiteUserRepository::findById(const std::string &userId)
{
    const std::string sql = "SELECT * FROM Users WHERE user_id = '" + userId + "'";
    auto const connection = m_connection.lock();
    if (!connection)
    {
        return std::nullopt;
    }

    SQLite::Statement query(*connection->connection(), sql);
    if (query.executeStep())
    {
        return User{ query.getColumn(0).getText(), query.getColumn(1).getText(), query.getColumn(2).getText(), query.getColumn(3).getText(), query.getColumn(4).getText()};
    }

    return std::nullopt;
}

std::optional<User> SQLiteUserRepository::findByUserName(const std::string &userName)
{
    return std::nullopt;
}

std::optional<User> SQLiteUserRepository::findByEmail(const std::string &email)
{
    return std::nullopt;
}