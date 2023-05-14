#ifndef _ITEMS_H_
#define _ITEMS_H_

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


void create_flashlight(int max_x,int max_y, char **map);


//void remove_flashlight(int max_x,int max_y,  char **map);

void creat_guns(int max_x,int max_y, char **map);

void remove_item (Position pos,char **map);

int whats_around(Position pos, char **map);

Position collected(Position pos, char **map);


#endif