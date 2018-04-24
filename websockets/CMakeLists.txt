cmake_minimum_required(VERSION 3.9)

project(websockets)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/lib/websocketpp)

find_package(Boost REQUIRED system)

add_executable(example main.cpp)
target_link_libraries(example Boost::system)

add_executable(server server.cpp)
target_link_libraries(server Boost::system)
