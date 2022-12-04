include(CTest)
set(TST_PROJECT_NAME ${CMAKE_PROJECT_NAME}_tst)
 
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cc)
 
set(SOURCES ${TEST_SOURCES})
 
add_executable(${TST_PROJECT_NAME} ${TEST_SOURCES})
 
add_test(NAME ${TST_PROJECT_NAME} COMMAND ${TST_PROJECT_NAME})

target_include_directories(${TST_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/depends/libull/include)
target_link_libraries(${TST_PROJECT_NAME} PUBLIC ${PROJECT_NAME}_lib gtest ${PROJECT_SOURCE_DIR}/depends/libull/lib/libull.a)
 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test)
