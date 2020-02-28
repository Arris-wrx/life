cmake_minimum_required(VERSION 3.5)

set(DCMAKE_SH="CMAKE_SH-NOTFOUND")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

add_executable(main_test main_test.cpp)
target_link_libraries(main_test matrix)

add_test(main_test "./main_test")
