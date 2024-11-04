cmake_minimum_required(VERSION 3.10)

project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/client/include)
include_directories(${CMAKE_SOURCE_DIR}/libs)

add_executable(client
    ${CMAKE_SOURCE_DIR}/client/src/client.cpp
    ${CMAKE_SOURCE_DIR}/client/src/communication.cpp
    ${CMAKE_SOURCE_DIR}/client/src/board.cpp
    ${CMAKE_SOURCE_DIR}/client/src/console_utils.cpp
    ${CMAKE_SOURCE_DIR}/client/src/format_message.cpp
    ${CMAKE_SOURCE_DIR}/client/src/game_manager.cpp
    ${CMAKE_SOURCE_DIR}/client/src/game_modes.cpp
    ${CMAKE_SOURCE_DIR}/client/src/player.cpp
    ${CMAKE_SOURCE_DIR}/libs/pugixml.cpp
)