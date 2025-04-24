cmake_minimum_required(VERSION 3.10)
project(homework_chess)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(homework_chess
        src/main.cpp
        src/Chess.cpp
        src/Rook.cpp
        src/Board.cpp
        src/King.cpp
        src/Bishop.cpp
        src/Queen.cpp
)

target_include_directories(homework_chess PRIVATE include)
