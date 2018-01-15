# CMakeLists.txt 
cmake_minimum_required(VERSION 3.6)

include("cmake/HunterGate.cmake")
HunterGate(
	URL "https://github.com/ruslo/hunter/archive/v0.16.15.tar.gz"
	SHA1 "6974c2150fc0d3b09de3ad1efcbf15d360647ffa"
)

project(ofstream)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

add_executable(write main.cpp)
target_link_libraries(write ${CMAKE_THREAD_LIBS_INIT})
