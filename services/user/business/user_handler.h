/*
* File: user_handler.h
* Author: trung.la
* Date: 03-23-2025
* Description: This file contains the declaration of the class UserHandler
* which is responsible for handling the business logic of the user service.
*/

#ifndef USER_HANDLER_H_
#define USER_HANDLER_H_

#include <memory>

class IUserRepository;
class User;

namespace user_service
{
    class CreateUserRequest;
} // namespace user_service

class UserHandler
{
public:
    using UserRepoUPtr = std::unique_ptr<IUserRepository>;
    using CreateUserRequest = user_service::CreateUserRequest;

    UserHandler(UserRepoUPtr user_repository);
    ~UserHandler() = default;

    User createUser(const CreateUserRequest &request);

private:
    UserRepoUPtr m_userRepo;
};
#endif // USER_HANDLER_H_