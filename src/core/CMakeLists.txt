cmake_minimum_required(VERSION 3.0)

include_directories(${PROJECT_SOURCE_DIR})

set(SRC_FILES Connection.cpp
              Dispatcher.cpp)

add_library(obj_core_lib OBJECT ${SRC_FILES} )

