cmake_minimum_required(VERSION 3.22)
project(microservices-system)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DDB_SOURCE_PATH="${CMAKE_SOURCE_DIR}/databases")

find_package(protobuf REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(httplib REQUIRED)
find_package(SQLiteCpp REQUIRED)
find_package(OpenSSL REQUIRED)

file(GLOB_RECURSE PROTO_FILES common/proto/*.proto)
# Generate protobuf source and header files
protobuf_generate(
    LANGUAGE cpp
    OUT_VAR PROTO_SOURCES
    IMPORT_DIRS ${CMAKE_SOURCE_DIR}/common/proto
    PROTOS ${PROTO_FILES}
)

set(COMMON_SOURCES
    common/database/IDatabaseConnection.h
    common/database/SQLiteConnection.h
    common/database/SQLiteConnection.cpp

    common/config_manager.h
    common/config_manager.cpp)

# common library defines the common code shared by all services: proto messages, config manager, etc.
add_library(common STATIC
    ${PROTO_SOURCES}
    ${COMMON_SOURCES})

target_include_directories(common
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(common
    PUBLIC
    protobuf::protobuf
    yaml-cpp
    SQLiteCpp)

# Define each service as an executable target.
set(SERVICES user)
set(user_SOURCES
    services/user/user_service.h
    services/user/business/user_handler.h
    services/user/data-structures/user.h
    services/user/data-structures/user.cpp
    services/user/repositories/IUserRepository.h
    services/user/repositories/SQLiteUserRepository.h

    services/user/user_service.cpp
    services/user/business/user_handler.cpp
    services/user/repositories/SQLiteUserRepository.cpp
    services/user/main.cpp)

add_executable(user_service
    ${user_SOURCES})

target_include_directories(user_service
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

foreach(SERVICE ${SERVICES})
   target_link_libraries(${SERVICE}_service
        common
        httplib::httplib
        openssl::openssl)
endforeach()

add_executable(gateway
    gateway/gateway_service.h
    gateway/gateway_service.cpp
    gateway/main.cpp)

target_include_directories(gateway
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gateway
 common
 httplib::httplib)