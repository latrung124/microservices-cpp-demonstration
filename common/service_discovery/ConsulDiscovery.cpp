/*
* File: ConsulDiscovery.cpp
* Author: trung.la
* Date: 03-26-2025
* Description: Implementation of service discovery using Consul
*/

#include "common/service_discovery/ConsulDiscovery.h"

ConsulDiscovery::ConsulDiscovery()
{
    // Initialize Consul client
    // ...
}

std::vector<std::string> ConsulDiscovery::discover(const std::string& name)
{
    // Discover services by name
    // ...
    return m_urls;
}

void ConsulDiscovery::registerService(const std::string &name, const std::string &url, int port)
{
    // Register service with Consul
    // ...
    m_serviceMap[name].push_back(url);
}

void ConsulDiscovery::unregisterService(const std::string &name, const std::string &url, int port)
{
    // Unregister service with Consul
    // ...
    auto it = std::find(m_serviceMap[name].begin(), m_serviceMap[name].end(), url);
    if (it != m_serviceMap[name].end())
    {
        m_serviceMap[name].erase(it);
    }
}