cmake_minimum_required(VERSION 3.0)

include_directories(${PROJECT_SOURCE_DIR})

set(SRC_FILES Config.cpp
              File.cpp
              Utils.cpp
#              BlockingQueue.h
              BlockingQueue.h)

add_library(obj_common_lib OBJECT ${SRC_FILES} )

