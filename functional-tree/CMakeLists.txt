# CMakeLists.txt 
cmake_minimum_required(VERSION 3.6)

include("cmake/HunterGate.cmake")
HunterGate(
	URL "https://github.com/ruslo/hunter/archive/v0.16.15.tar.gz"
	SHA1 "6974c2150fc0d3b09de3ad1efcbf15d360647ffa"
)

project(functional-tree)

set(CMAKE_CXX_STANDARD 17)

# this block add warning flags, taken from stackoverflow
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

hunter_add_package(nod)
find_package(nod CONFIG REQUIRED)

add_executable(tree main.cpp)
target_link_libraries(tree nod::nod)
