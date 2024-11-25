cmake_minimum_required(VERSION 3.10)
project(ServerLogicTests)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_server_logic 
    test/test_server_logic.cpp
    src/server_logic.cpp
)

include_directories(include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_compile_definitions(test_server_logic PRIVATE TEST_ENVIRONMENT)

target_link_libraries(test_server_logic ${GTEST_LIBRARIES} pthread)