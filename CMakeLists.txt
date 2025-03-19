cmake_minimum_required(VERSION 3.22)
project(microservices-system)

set(CMAKE_CXX_STANDARD 20)

find_package(protobuf REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(httplib REQUIRED)

set(COMMON_SOURCES
    common/config_manager.h
    common/config_manager.cpp)

add_executable(gateway
    gateway/main.cpp
    ${COMMON_SOURCES})

target_link_libraries(gateway protobuf::protobuf)