#include <iostream>

#include "common/database/SQLiteConnection.h"
#include "services/user/repositories/SQLiteUserRepository.h"
#include "services/user/business/user_handler.h"
#include "services/user/user_service.h"

int main()
{
    std::cout << "User service is running..." << std::endl;

    auto connection = std::make_shared<SQLiteConnection>(std::string(DB_SOURCE_PATH) + "/Users.db");
    auto repo = std::make_unique<SQLiteUserRepository>(connection);
    UserService service(50051, std::move(repo));
    service.start();

    return EXIT_SUCCESS;
}