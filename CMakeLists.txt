cmake_minimum_required(VERSION 3.5)

set(DCMAKE_SH="CMAKE_SH-NOTFOUND")

project(life LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(life src/main.cpp)
target_include_directories(life PUBLIC ${PROJECT_SOURCE_DIR}/include)

