/*
* File: gateway_service.h
* Author: trung.la
* Date: 03-23-2025
* Description: This file contains the definitions of the GatewayService class.
* This class is responsible for handling the communication between the client and the other services.
*/

#ifndef GATEWAY_SERVICE_H
#define GATEWAY_SERVICE_H

#include <memory>

#include <httplib.h>

class ConfigManager;

class GatewayService
{
public:
    using ConfigManagerPtr = std::shared_ptr<ConfigManager>;
    using HttpClientPtr = std::shared_ptr<httplib::Client>;
    GatewayService(ConfigManagerPtr config);

    void start();

private:
    ConfigManagerPtr m_config;
    HttpClientPtr m_httpClient;
};
#endif // GATEWAY_SERVICE_H