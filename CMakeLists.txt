cmake_minimum_required(VERSION 3.5)

set(DCMAKE_SH="CMAKE_SH-NOTFOUND")

project(life LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB hdrs ${PROJECT_SOURCE_DIR}/include/*.h*)
file(GLOB srcs ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(include src)
add_library(matrix STATIC ${srcs} ${hdrs})

link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(app)
add_subdirectory(tests)

