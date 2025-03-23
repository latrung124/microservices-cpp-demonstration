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
#include "services/user/business/user_handler.h"
#include "services/user/repositories/IUserRepository.h"

UserService::UserService(int port, IUserRepoUPtr userRepo)
    : m_port(port),
    m_userRepo(std::move(userRepo))
{
    m_userHandler = std::make_unique<UserHandler>(std::move(m_userRepo));
}

void UserService::start()
{
    /**
     * Define an HTTP Post route at /users
     * Lambda function is the request handler for this route
     */
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
        user_service::User userProto;
        userProto.set_username(user.getUserName());
        userProto.set_email(user.getEmail());
        res.set_content(userProto.SerializeAsString(), "application/protobuf");
    });

    // Start the server listening on localhost and the specified port
    m_server.listen("localhost", m_port);
}