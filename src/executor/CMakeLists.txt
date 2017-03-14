cmake_minimum_required(VERSION 3.0)

include_directories(${PROJECT_SOURCE_DIR})

set(SRC_FILES IJob.cpp
              JobExecutor.cpp
              JobFactory.cpp)

add_library(obj_executor_lib OBJECT ${SRC_FILES} )

