cmake_minimum_required(VERSION 3.15)
project(game C)

set(CMAKE_C_STANDARD 99)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(game main.c)
target_link_libraries(game ${CURSES_LIBRARIES} -I/usr/include/ncursesw -lncursesw -ltinfo)



