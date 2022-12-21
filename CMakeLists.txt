cmake_minimum_required(VERSION 3.11)
project(Bookstore)

set(CMAKE_CXX_FLAGS "-g -O2 -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Main sources
include_directories(${PROJECT_SOURCE_DIR}/src)
# add_subdirectory(src)

# Test
# add_subdirectory(test)

file(GLOB SRC_LIST
    src/*.cc
    src/Book/*.cc
    src/File/*.cc
    src/List/*.cc
    src/Utils/*.cc
    src/User/*.cc
)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_executable(code ${SRC_LIST})
