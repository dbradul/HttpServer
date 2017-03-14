cmake_minimum_required(VERSION 3.0)

include_directories(${PROJECT_SOURCE_DIR})

set(SRC_FILES Constants.cpp
              Message.cpp
              Request.cpp
              Response.cpp)

add_library(obj_protocol_lib OBJECT ${SRC_FILES} )

