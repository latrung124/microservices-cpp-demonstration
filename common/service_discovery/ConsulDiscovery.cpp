/*
* File: ConsulDiscovery.cpp
* Author: trung.la
* Date: 03-26-2025
* Description: Implementation of service discovery using Consul
*/

#include "common/service_discovery/ConsulDiscovery.h"

ConsulDiscovery::ConsulDiscovery(std::string_view addr, int port, bool enabledHealthCheck)
    : m_client(addr.data(), port)
    m_enabledHealthCheck(enabledHealthCheck)
{
    // Initialize Consul client
    // ...
}

std::vector<std::string> ConsulDiscovery::discover(const std::string& name)
{
    // Discover services by name
    // ...
    return {};
}

void ConsulDiscovery::registerService(const std::string &name, const std::string &url, int port)
{
    // Register service with Consul
    // ...
    static const std::string healthCheckPath = "/health";

    nlohmann::json payload = {
        {"ID", name + "-" + std::to_string(port)},
        {"Name", name},
        {"Address", url},
        {"Port", port},
        {"Check", {
            {"HTTP", "http://" + url + ":" + std::to_string(port) + healthCheckPath},
            {"Interval", "10s"},
            {"Timeout", "5s"},
            {"DeregisterCriticalServiceAfter", "5m"}
        }}
    };

    auto res = m_client.Put("/v1/agent/service/register", payload.dump(), "application/json");

    if (!res || res->status != 200) {
        throw::std::runtime_error("Service registration failed: " + res ? res->body : "no response");
    }
}

void ConsulDiscovery::unregisterService(const std::string &name, const std::string &url, int port)
{
    // Unregister service with Consul
    // ...
}