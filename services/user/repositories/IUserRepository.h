/*
* File: IUserRepository.h
* Author: trung.la
* Date: 03-22-2025
* Description: This file contains the declaration of the IUserRepository interface.
*/

#ifndef IUSER_REPOSITORY_H
#define IUSER_REPOSITORY_H

#include <string>
#include <vector>
#include <optional>

#include "services/user/data-structures/User.h"

class IUserRepository
{
public:
    virtual ~IUserRepository() = default;
    virtual void createTable() = 0;
    virtual void insert(const User& user) = 0;
    virtual void update(const User& user) = 0;
    virtual void remove(const User& user) = 0;
    virtual std::vector<User> getAll() = 0;
    virtual std::optional<User> findById(const std::string& userId) = 0;
    virtual std::optional<User> findByUserName(const std::string& userName) = 0;
    virtual std::optional<User> findByEmail(const std::string& email) = 0;
};

#endif // IUSER_REPOSITORY_H