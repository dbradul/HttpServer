cmake_minimum_required(VERSION 3.0)

project(HttpServer)

set(${PROJECT_NAME}_LIB "${PROJECT_NAME}_LIB")
set(SRC_DIR src)
set(TESTS_DIR unittests)

add_subdirectory(${SRC_DIR})
add_subdirectory(${TESTS_DIR})

