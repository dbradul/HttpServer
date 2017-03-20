cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -Wall -g")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(.)

message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
add_subdirectory(protocol)
add_subdirectory(core)
add_subdirectory(builder)
add_subdirectory(common)
add_subdirectory(executor)

set(obj_libs $<TARGET_OBJECTS:obj_protocol_lib>
             $<TARGET_OBJECTS:obj_core_lib>
             $<TARGET_OBJECTS:obj_builder_lib>
             $<TARGET_OBJECTS:obj_common_lib>
             $<TARGET_OBJECTS:obj_executor_lib>)

add_library(${PROJECT_NAME}_LIB ${obj_libs})
add_executable(${PROJECT_NAME} Main.cpp ${obj_libs})
target_link_libraries(${PROJECT_NAME} pthread)

