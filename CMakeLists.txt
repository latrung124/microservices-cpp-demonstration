cmake_minimum_required(VERSION 3.22)
project(microservices-system)

set(CMAKE_CXX_STANDARD 20)

find_package(protobuf REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(httplib REQUIRED)
find_package(SQLiteCpp REQUIRED)

file(GLOB_RECURSE PROTO_FILES common/proto/*.proto)
protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${PROTO_FILES})

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
    protobuf::protobuf
    yaml-cpp
    SQLiteCpp)

# Define each service as an executable target.
set(SERVICES user)
set(user_SOURCES
    services/user/data-structures/user.h
    services/user/data-structures/user.cpp
    services/user/repositories/IUserRepository.h
    services/user/repositories/SQLiteUserRepository.h
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
        protobuf::protobuf
        yaml-cpp)
endforeach()

add_executable(gateway
    gateway/main.cpp)

target_link_libraries(gateway
 common
 protobuf::protobuf
 yaml-cpp)