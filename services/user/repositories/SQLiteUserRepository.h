/*
* File: SQLiteUserRepository.h
* Author: trung.la
* Date: 03-22-2025
* Description: This file contains the declaration of the SQLiteUserRepository class.
*/

#ifndef SQLITE_USER_REPOSITORY_H
#define SQLITE_USER_REPOSITORY_H

#include <memory>

#include "common/database/IDatabaseConnection.h"

#include "services/user/repositories/IUserRepository.h"

class SQLiteUserRepository : public IUserRepository
{
public:
    explicit SQLiteUserRepository(const std::shared_ptr<IDatabaseConnection> &connection);
    SQLiteUserRepository() = default;
    ~SQLiteUserRepository() override = default;

    void createTable() override;
    void insert(const User& user) override;
    void update(const User& user) override;
    void remove(const User& user) override;
    std::vector<User> getAll() override;
    std::optional<User> findById(const std::string& userId) override;
    std::optional<User> findByUserName(const std::string& userName) override;
    std::optional<User> findByEmail(const std::string& email) override;

private:
    std::weak_ptr<IDatabaseConnection> m_connection;
};

#endif // SQLITE_USER_REPOSITORY_H