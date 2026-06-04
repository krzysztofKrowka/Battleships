cmake_minimum_required(VERSION 4.1)
project(Battleships)

set(CMAKE_CXX_STANDARD 20)

add_executable(Battleships main.cpp
        Game.cpp
        Game.h
        Tile.cpp
        Tile.h
        miniaudio.h)
target_link_libraries(Battleships PRIVATE winmm ole32)