cmake_minimum_required(VERSION 3.10)
project(homework_chess)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)  # ← נוודא שהנתיב מוחלט

add_executable(homework_chess
        src/main.cpp
        src/Chess.cpp
        src/Rook.cpp
        src/Board.cpp
        src/King.cpp
        src/Bishop.cpp
        src/Queen.cpp
        src/Pawn.cpp
        src/Knight.cpp
        src/Move.cpp
        src/Utils.cpp
)

target_include_directories(homework_chess PRIVATE ${CMAKE_SOURCE_DIR}/include)
