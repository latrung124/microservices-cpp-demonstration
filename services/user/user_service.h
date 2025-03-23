/*
* File: user_service.h
* Author: trung.la
* Date: 03-23-2025
* Description: This file contains the declaration of the UserService class
* which is responsible for handling user-related operations.
*/

#ifndef USER_SERVICE_H_
#define USER_SERVICE_H_

#include <httplib.h>

class IUserRepository;
class UserHandler;

/**
 * @brief The UserService class is responsible for handling user-related operations.
 * Handling HTTP requests, parsing request data, and returning responses.
 * It acts as the entry point for the user service, connecting the external world(HTTP requests)
 * to the internal business logic (handlers and repositories)
 */
class UserService
{
public:
    using IUserRepoUPtr = std::unique_ptr<IUserRepository>;
    using UserHandlerUPtr = std::unique_ptr<UserHandler>;

    UserService(int port, IUserRepoUPtr userRepo);
    ~UserService() = default;

    void start();

private:
    int m_port = 0;
    httplib::Server m_server;
    IUserRepoUPtr m_userRepo;
    UserHandlerUPtr m_userHandler;
};

#endif // USER_SERVICE_H_