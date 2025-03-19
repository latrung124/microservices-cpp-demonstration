cmake_minimum_required(VERSION 3.22)
project(microservices-system)

set(CMAKE_CXX_STANDARD 20)

find_package(protobuf REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(httplib REQUIRED)

add_executable(gateway gateway/main.cpp)

target_link_libraries(gateway protobuf::protobuf)