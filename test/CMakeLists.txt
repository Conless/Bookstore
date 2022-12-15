include(CTest)
set(TST_PROJECT_NAME ${CMAKE_PROJECT_NAME}_tst)

# include_directories(${PROJECT_SOURCE_DIR}/depends/libull/include)
 
add_executable(code ull/test1.cc)
# add_test(${TST_PROJECT_NAME}_2 ull/test2.cc ${PROJECT_SOURCE_DIR}/src/List/UnrolledLinkedList.cc)

# target_link_libraries(${TST_PROJECT_NAME}_1 ${PROJECT_SOURCE_DIR}/depends/libull/lib/libull.a)
 
# add_test(NAME ${TST_PROJECT_NAME} COMMAND ${TST_PROJECT_NAME})
 
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test)
