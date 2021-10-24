#!/bin/bash
gcc   -O3 -DNDEBUG   -std=gnu99 -o game.o -c game.c
gcc   -O3 -DNDEBUG   -std=gnu99 -o main.o -c main.c
gcc   -O3 -DNDEBUG   -std=gnu99 -o game1 main.o game.o -I/usr/include/ncursesw -lncursesw -ltinfo

