cmake_minimum_required(VERSION 3.6)

project(qsnake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(SOURCE_FILES
        src/main.cpp
        src/qsnake.h
        src/qsnake.cpp
        src/constants.h
        src/game.h
        src/game.cpp
        src/snake.h
        src/snake.cpp
        src/board.h
        src/board.cpp)

find_package(Qt5Widgets REQUIRED)

add_executable(qsnake ${SOURCE_FILES})

target_link_libraries(qsnake Qt5::Widgets)