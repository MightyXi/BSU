cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_library(
        Numbers
        Number.h
        Number.cpp
)

include(GenerateExportHeader)
add_library(Vector SHARED Vector.cpp Vector.h)
generate_export_header(Vector)
target_include_directories(Vector PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})
add_executable(untitled main.cpp)

target_link_libraries(untitled PRIVATE Numbers)
target_link_libraries(untitled PRIVATE Vector)