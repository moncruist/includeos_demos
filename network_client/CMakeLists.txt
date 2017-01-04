cmake_minimum_required(VERSION 3.7)
project(network_client)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED system)

set(SOURCE_FILES main.cpp)
add_executable(network_client ${SOURCE_FILES})
target_link_libraries(network_client ${Boost_LIBRARIES})