cmake_minimum_required(VERSION 3.22)
project(microservices-system)

set(CMAKE_CXX_STANDARD 20)

add_executable(gateway gateway/main.cpp)