/*
* File: user_handler.cpp
* Author: trung.la
* Date: 03-23-2025
* Description: This file contains the definitions of the class UserHandler
*/

#include "services/user/business/user_handler.h"

#include "user_service.pb.h"

#include "services/user/data-structures/User.h"
#include "services/user/repositories/SQLiteUserRepository.h"

UserHandler::UserHandler(UserRepoUPtr user_repository)
    : m_userRepo(std::move(user_repository))
{
}

User UserHandler::createUser(const CreateUserRequest &request)
{
    User user;
    user.setUserName(request.username());
    user.setEmail(request.email());
    m_userRepo->insert(user);
    return user;
}