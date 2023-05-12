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


void remove_flashlight(int max_x,int max_y,  char **map);

#endif