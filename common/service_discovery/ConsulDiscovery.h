/*
* File: ConsulDiscovery.h
* Author: trung.la
* Date: 03-26-2025
* Description: Implementation of service discovery using Consul
* Consul is a distributed service mesh to connect, secure, and configure services across any runtime platform and public or private cloud
*/

#ifndef CONSULDISCOVERY_H_
#define CONSULDISCOVERY_H_

#include <unordered_map>

#include "common/service_discovery/IServiceDiscovery.h"

class ConsulDiscovery : public IServiceDiscovery
{
public:
    ConsulDiscovery();
    virtual ~ConsulDiscovery() = default;

    virtual std::vector<std::string> discover(const std::string& name) override;
    virtual void registerService(const std::string &name, const std::string &url, int port) override;
    virtual void unregisterService(const std::string &name, const std::string &url, int port) override;

private:
    std::vector<std::string> m_urls;
    std::unordered_map<std::string, std::vector<std::string>> m_serviceMap;
};

#endif // CONSULDISCOVERY_H_