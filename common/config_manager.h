/*
* File: config_manager.h
* Author: trung.la
* Date: 03-19-2025
* Description: This file contains the declaration of the ConfigManager class.
*/

#ifndef COMMON_CONFIG_MANAGER_H_
#define COMMON_CONFIG_MANAGER_H_

#include <string_view>
#include <unordered_map>

class ConfigManager
{
public:
    ConfigManager(std::string_view configPath);
    ~ConfigManager() = default;

    std::string getServiceUrl(const std::string &serviceName) const;

private:
    std::string m_env;
    std::unordered_map<std::string, std::string> m_services;
};

#endif // COMMON_CONFIG_MANAGER_H_