/*
* File: config_manager.cpp
* Author: trung.la
* Date: 03-19-2025
* Description: This file contains the implementation of the ConfigManager class.
*/

#include "config_manager.h"

#include <yaml-cpp/yaml.h>

ConfigManager::ConfigManager(std::string_view configPath)
{
    // Load configuration from yaml file
    YAML::Node config = YAML::LoadFile(std::string(configPath));
    m_env = config["environment"].as<std::string>();

    for (const auto &service : config["services"]) {
        m_services[service.first.as<std::string>()] =
        m_env == "cloud" ? service.second["cloud"].as<std::string>() : service.second["local"].as<std::string>();
    }
}

std::string ConfigManager::getServiceUrl(const std::string &serviceName) const
{
    // Get service URL from configuration
    // ...
    auto it = m_services.find(serviceName);
    if (it != m_services.end())
    {
        return it->second;
    } else {
        return "";
    }
}