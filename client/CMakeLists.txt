cmake_minimum_required(VERSION 3.10)

project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

# Add directories with header files
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../libs)

# Creating a library with shared code
add_library(tictactoe_lib
    ${CMAKE_SOURCE_DIR}/src/communication.cpp
    ${CMAKE_SOURCE_DIR}/src/board.cpp
    ${CMAKE_SOURCE_DIR}/src/console_utils.cpp
    ${CMAKE_SOURCE_DIR}/src/format_message.cpp
    ${CMAKE_SOURCE_DIR}/src/game_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/game_modes.cpp
    ${CMAKE_SOURCE_DIR}/src/player.cpp
    ${CMAKE_SOURCE_DIR}/../libs/pugixml.cpp
)

# The main client executable file
add_executable(client
    ${CMAKE_SOURCE_DIR}/src/client.cpp
)
target_link_libraries(client tictactoe_lib)

# Enable testing
enable_testing()

# Google Test download
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Add an executable file for tests
add_executable(client_tests
    ${CMAKE_SOURCE_DIR}/tests/test_board.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_console_utils.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_format_message.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_game_manager.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_game_modes.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_player.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_communication.cpp
)

# Connect Google Test libraries to the test executable
target_link_libraries(client_tests
    gtest
    gtest_main
    gmock
    gmock_main
    tictactoe_lib
)

# Automatic test detection
include(GoogleTest)
gtest_discover_tests(client_tests)