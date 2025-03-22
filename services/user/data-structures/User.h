/*
* File: User.h
* Author: trung.la
* Date: 03-22-2025
* Description: This file contains the declaration of the User class.
*/

#ifndef USER_H
#define USER_H

#include <string>

/**
 * @brief The User class
 * This class represents a user in the system.
 * It contains the user's ID, name, email, createAt and updateAt.
 * The class provides getter and setter methods for each attribute.
 * The class is used to store user information to database.
 */
class User
{
public:
    User() = default;
    User(const std::string& userId, const std::string& userName, const std::string& email, const std::string& createAt, const std::string& updateAt);
    ~User() = default;

    std::string getUserId() const;
    void setUserId(const std::string& userId);

    std::string getUserName() const;
    void setUserName(const std::string& userName);

    std::string getEmail() const;
    void setEmail(const std::string& email);

    std::string getCreateAt() const;
    void setCreateAt(const std::string& createAt);

    std::string getUpdateAt() const;
    void setUpdateAt(const std::string& updateAt);

private:
    std::string m_userId;
    std::string m_userName;
    std::string m_email;
    std::string m_createAt;
    std::string m_updateAt;
};

#endif // USER_H