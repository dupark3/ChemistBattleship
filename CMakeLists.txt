set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.5.1)
project(PeriodicTableBattleship)
add_executable(PeriodicTableBattleship main.cpp periodic_table.cpp player.cpp AI.cpp gameboard.cpp game.cpp)