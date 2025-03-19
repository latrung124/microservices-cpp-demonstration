/*
* File: config_manager.cpp
* Author: trung.la
* Date: 03-19-2025
* Description: This file contains the implementation of the ConfigManager class.
*/

#include "config_manager.h"

ConfigManager::ConfigManager(std::string_view configPath)
{
    // Load configuration from yaml file
    // ...
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