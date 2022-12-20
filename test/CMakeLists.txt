include(CTest)
set(TST_PROJECT_NAME ${CMAKE_PROJECT_NAME}_tst)

set(CMAKE_CXX_FLAGS "-g -std=c++17")
add_executable(${TST_PROJECT_NAME}_1 ull/test1.cc ${PROJECT_SOURCE_DIR}/src/List/UnrolledLinkedList.cc)
add_executable(${TST_PROJECT_NAME}_2 book/test2.cc ${PROJECT_SOURCE_DIR}/src/List/UnrolledLinkedList.cc ${PROJECT_SOURCE_DIR}/src/Book/BookSystem.cc ${PROJECT_SOURCE_DIR}/src/Utils/TokenScanner.cc)
# add_test(${TST_PROJECT_NAME}_2 ull/test2.cc ${PROJECT_SOURCE_DIR}/src/List/UnrolledLinkedList.cc)
 
# add_test(NAME ${TST_PROJECT_NAME} COMMAND ${TST_PROJECT_NAME})
 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/test)
