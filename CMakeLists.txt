cmake_minimum_required(VERSION 4.0)
project(Chess)

set(CMAKE_CXX_STANDARD 23)

add_executable(Chess main.cpp
        boardFunctions.cpp
        boardFunctions.h
        chessBot.cpp
        chessBot.h)

find_package(OpenMP REQUIRED)
target_link_libraries(Chess OpenMP::OpenMP_CXX)