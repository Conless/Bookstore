cmake_minimum_required(VERSION 3.16)

project(libull)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Ofast -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(code src/main.cpp)
target_include_directories(code PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_directories(code PUBLIC ${PROJECT_SOURCE_DIR}/lib/)
target_link_libraries(code ull)
