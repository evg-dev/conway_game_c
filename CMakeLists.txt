cmake_minimum_required(VERSION 3.15)
project(game_life)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON -G Unix Makefiles)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(game main.c game.c)
target_link_libraries(game -I/usr/include/ncursesw -lncursesw -ltinfo)



