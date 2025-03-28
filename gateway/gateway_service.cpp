/*
* File: gateway_service.cpp
* Author: trung.la
* Date: 03-23-2025
* Description: This file contains the definitions of the GatewayService class.
*/

#include "gateway/gateway_service.h"

#include "common/config_manager.h"
#include "common/service_discovery/ConsulDiscovery.h"

GatewayService::GatewayService(ConfigManagerPtr config)
    : m_config(config)
    , m_discovery(std::make_unique<ConsulDiscovery>())
{
}

GatewayService::~GatewayService()
{
}

void GatewayService::start()
{
    // Start the gateway service
    using namespace httplib;

    if (!m_config) {
        return;
    }

    std::string url = m_config->getServiceUrl("user_service");
    if (url.empty()) {
        return;
    }

    m_httpClient = std::make_shared<Client>("localhost", 50051);
 
    Server server;

    server.Post("/api/users", [&](const Request &req, Response &res) {
        std::cout << "Received POST request to create user!" << std::endl;
        if (!m_config) {
            res.status = 500;
            res.set_content("Internal server error", "text/plain");
            return;
        }

        if (!m_httpClient) {
            res.status = 500;
            res.set_content("Internal server error", "text/plain");
            return;
        }

        auto serviceRes = m_httpClient->Post("/users", req.body, "application/protobuf");
        if (!serviceRes) {
            res.status = 500;
            res.set_content("Internal server error", "text/plain");
            return;
        }
        res.set_content(serviceRes->body, "application/protobuf");

        std::cout << "User created successfully!" << std::endl;
    });

    std::cout << "Gateway service listening on port 8080" << std::endl;

    server.listen("localhost", 8080);
}

void GatewayService::handleRequest()
{
    auto instances = m_discovery->discover("user_service");

    if(instances.empty()) {
        throw std::runtime_error("No instances found for user_service");
    }

    //Use instances...
}