/*
* File: IServiceDiscovery.h
* Author: trung.la
* Date: 03-26-2025
* Description: Interface for service discovery
*/

#ifndef ISERVICEDISCOVERY_H_
#define ISERVICEDISCOVERY_H_

#include <string>
#include <vector>

class IServiceDiscovery
{
public:
    virtual ~IServiceDiscovery() = default;

    virtual std::vector<std::string> discover(const std::string &name) = 0;
    virtual void registerService(const std::string &name, const std::string &url, int port) = 0;
    virtual void unregisterService(const std::string &name, const std::string &url, int port) = 0;
};

#endif // ISERVICEDISCOVERY_H_