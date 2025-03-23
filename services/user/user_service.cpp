/*
* File: user_service.cpp
* Author: trung.la
* Date: 03-23-2025
* Description: This file contains the implementation of the UserService class
* which is responsible for handling user-related operations.
*/

#include "services/user/user_service.h"

#include <iostream>

#include <user_service.pb.h>

#include "services/user/data-structures/User.h"
#include "services/user/handlers/UserHandler.h"

UserService::UserService(int port, IUserRepoUPtr userRepo)
    : m_port(port),
    m_userRepo(std::move(userRepo)),
    m_userHandler(std::make_unique<UserHandler>(m_userRepo))
{
}

void UserService::start()
{
    m_server.Post("/users", [&](const httplib::Request& req, httplib::Response& res) {
        std::cout << "Received POST request to create user!" << std::endl;

        user_service::CreateUserRequest request;
        try {
            request.ParseFromString(req.body);
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content("Invalid request body", "text/plain");
            return;
        }

        User user = m_userHandler->createUser(request);
        res.set_content(user.toProtobuf().SerializeAsString(), "application/protobuf");
    });

    svr.listen("localhost", m_port);
}