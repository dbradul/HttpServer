cmake_minimum_required(VERSION 3.0)

include_directories(${PROJECT_SOURCE_DIR})

set(SRC_FILES PageBuilder.cpp
              HTMLDecorator.cpp
              Templater.cpp)

add_library(obj_builder_lib OBJECT ${SRC_FILES} )

