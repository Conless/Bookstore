set(PROJECT_NAME ${CMAKE_PROJECT_NAME})

# include_directories(${PROJECT_SOURCE_DIR}/depends/libull/include)

file(GLOB SRC_LIST
    *.cc
    Book/*.cc
    File/*.cc
    Utils/*.cc
    User/*.cc
)

add_executable(${PROJECT_NAME}_run ${SRC_LIST})


# target_link_libraries(${PROJECT_NAME}_run ${PROJECT_SOURCE_DIR}/depends/libull/lib/libull.a)

add_library(${PROJECT_NAME}_lib STATIC ${SRC_LIST})
