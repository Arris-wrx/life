cmake_minimum_required(VERSION 3.5)

set(DCMAKE_SH="CMAKE_SH-NOTFOUND")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g")

add_executable(life main.cpp)
target_link_libraries(life matrix)

set_target_properties(life PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
