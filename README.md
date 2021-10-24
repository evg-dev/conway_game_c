# Conway's Game of Life  

Console game on C99 with ncurses   

![Image screen](https://raw.githubusercontent.com/evg-dev/conway_game_life/master/game.png)

Game begin on pause. 

Control the cursor and fill in the points on the grid by pressing the ENTER on the point.

Unpause by pressing P and watch autogeneration, or use manual mode by pressing the SPACE.

You can change points on the grid in the process by pausing the game and switching back to manual mode.

To start new game press N

Exit - ESC ot Ctrl+C 

## Compile

install ncurses 

```
apt-get install libncurses5-dev libncursesw5-dev
```

Use [CmakeLilst.txt](https://github.com/evg-dev/conway_game_life/blob/master/CMakeLists.txt) or [release_compile.sh](https://github.com/evg-dev/conway_game_life/blob/master/release_compile.sh)


## Binary
[linux x86_64](https://github.com/evg-dev/conway_game_life/blob/master/cmake-build-release/game)