# CMakeLists.txt 
cmake_minimum_required(VERSION 3.5)

# remember to set HUNTER_ROOT env variable!
include("cmake/HunterGate.cmake")
HunterGate(
	URL "https://github.com/ruslo/hunter/archive/v0.16.15.tar.gz"
	SHA1 "6974c2150fc0d3b09de3ad1efcbf15d360647ffa"
)

project(asio)

hunter_add_package(Boost COMPONENTS system thread)
find_package(Boost CONFIG REQUIRED system thread)
set(CMAKE_CXX_STANDARD 17)

add_executable(one one.cpp)
target_link_libraries(one Boost::system Boost::thread)

add_executable(two two.cpp)
target_link_libraries(two Boost::system Boost::thread)

add_executable(three three.cpp)
target_link_libraries(three Boost::system Boost::thread)

add_executable(four four.cpp)
target_link_libraries(four Boost::system Boost::thread)

add_executable(five five.cpp)
target_link_libraries(five Boost::system Boost::thread)
