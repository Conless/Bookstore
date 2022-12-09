# cmake_minimum_required(VERSION 3.22)
# project(Bookstore)

# set(CMAKE_CXX_FLAGS "-g")
# set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# # Main sources
# include_directories(${PROJECT_SOURCE_DIR}/src)
# add_subdirectory(src)

# # Test
# add_subdirectory(test)
# add_subdirectory(depends/googletest)
cmake_minimum_required(VERSION 3.15)
project(Bookstore)

set(CMAKE_CXX_FLAGS "-Ofast")

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(code ${PROJECT_SOURCE_DIR}/test/test.cc ${PROJECT_SOURCE_DIR}/src/List/UnrolledLinkedList.cc)
