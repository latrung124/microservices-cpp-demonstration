/*
* File: ConsulDiscovery.cpp
* Author: trung.la
* Date: 03-26-2025
* Description: Implementation of service discovery using Consul
*/

#include "common/service_discovery/ConsulDiscovery.h"

#include <algorithm>
#include <stdexcept>

#include <nlohmann/json.hpp>

ConsulDiscovery::ConsulDiscovery(std::string_view addr, int port, bool enabledHealthCheck)
    : m_client(addr.data(), port)
    , m_enabledHealthCheck(enabledHealthCheck)
{
    // Initialize Consul client
    // ...
}

std::vector<std::string> ConsulDiscovery::discover(const std::string& name)
{
    using namespace nlohmann;
    using namespace httplib;

    std::string path = "/v1/health/service/" + name;

    httplib::Result res = m_client.Get(path.c_str());
    if (!res || res->status != 200) {
        return {};
    }

    json instance = nlohmann::json::parse(res->body);
    std::vector<std::string> healthyInstances;
    for (const auto &entry : instance) {
        bool healthy = std::all_of(entry["Checks"].begin(), entry["Checks"].end(), [](const auto &check) {
            return check["Status"] == "passing";
        });

        if (healthy || !m_enabledHealthCheck) {
            const auto &service = entry["Service"];
            std::string address = service["Address"].get<std::string>();
            if (address.empty()) address = getLocalIp();
            healthyInstances.emplace_back(
                address + ":" + std::to_string(service["Port"].get<int>())
            );
        }
    }
    return healthyInstances;
}

void ConsulDiscovery::registerService(const std::string &name, const std::string &url, int port)
{
    // Register service with Consul
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

std::string ConsulDiscovery::getLocalIp()
{
    //TODO: replace with actual implementation in future
    return "127.0.0.1";
}