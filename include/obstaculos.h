#ifndef _OBSTACULOS_H_
#define _OBSTACULOS_H_

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

void create_Triangle(Position pos, int max_x, int max_y, char **map);

void create_Square(Position pos, int max_x, int max_y, char **map);

void create_Circle(Position pos,int max_x, int max_y, char **map);

void create_barrel(int max_x,int max_y, char **map);

#endif