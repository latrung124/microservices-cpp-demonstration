#include <iostream>

#include "gateway/gateway_service.h"
#include "common/config_manager.h"

int main() {
    std::cout << "Gateway!" << std::endl;
    auto config = std::make_shared<ConfigManager>("config/config.yaml");
    GatewayService gateway(config);
    gateway.start();
    return EXIT_SUCCESS;
}