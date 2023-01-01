set(PROJECT_NAME ${CMAKE_PROJECT_NAME})

file(GLOB SRC_LIST
    *.cc
    Book/*.cc
    Files/*.cc
    List/*.cc
    Utils/*.cc
    User/*.cc
    Log/*.cc
)

set(CMAKE_CXX_FLAGS "-g -std=c++17")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME}_run ${SRC_LIST})

add_library(${PROJECT_NAME}_lib STATIC ${SRC_LIST})
