set(PROJECT_NAME ${CMAKE_PROJECT_NAME})

# include_directories(${PROJECT_SOURCE_DIR}/depends/libull/include)

file(GLOB SRC_LIST
    *.cc
    Book/*.cc
    File/*.cc
    List/*.cc
    Utils/*.cc
    User/*.cc
)

set(CMAKE_CXX_FLAGS "-g -std=c++17")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME}_run ${SRC_LIST})

# target_link_libraries(${PROJECT_NAME}_run ${PROJECT_SOURCE_DIR}/depends/libull/lib/libull.a)

add_library(${PROJECT_NAME}_lib STATIC ${SRC_LIST})
