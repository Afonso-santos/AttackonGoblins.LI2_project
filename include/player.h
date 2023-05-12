#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdbool.h>
#include <alloca.h>
#include <string.h>
#include <curses.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/estruturas.h"

int check(int x, int y,int max_x,int max_y, char **map);

int check_player(int x, int y,int max_x,int max_y, char **map);

void move_player(player player, int max_x, int max_y, char **map);

player create_coordinates(int max_x,int max_y, char **map);

#endif