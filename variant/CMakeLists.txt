# CMakeLists.txt 
cmake_minimum_required(VERSION 3.6)

project(variant)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")
endif()

add_executable(variant main.cpp)
