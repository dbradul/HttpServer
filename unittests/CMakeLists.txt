cmake_minimum_required(VERSION 3.0)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -Wall -pedantic")
include_directories(${PROJECT_SOURCE_DIR}/src)
message("Unittests project! Linked with lib: ${PROJECT_NAME}_LIB")

# Add test cpp file
add_executable(runUnitTests
    AllTests.cpp
    FileTest.cpp
    ConfigTest.cpp
    MessageTest.cpp
)

# Link test executable against gtest & main lib
target_link_libraries(runUnitTests ${PROJECT_NAME}_LIB ${GTEST_BOTH_LIBRARIES})

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)
