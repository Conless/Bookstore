set(PROJECT_NAME ${CMAKE_PROJECT_NAME})

file(GLOB SRC_LIST
    *.cc
    book/*.cc
    file/*.cc
    tools/*.cc
    user/*.cc
)

add_executable(${PROJECT_NAME}_run ${SRC_LIST})

add_library(${PROJECT_NAME}_lib STATIC ${SRC_LIST})
