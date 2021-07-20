cmake_minimum_required(VERSION 3.17)
project(AI_TICTACTOE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/)
# add_library(board include/Board.h )
add_executable(main src/main.cpp src/Board.cpp src/Game.cpp src/minmax_ai.cpp)
# target_link_libraries(main board)