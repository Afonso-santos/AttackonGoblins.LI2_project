#ifndef _COMBAT_H_
#define _COMBAT_H_

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

void enemy_combat(player player, Enemy enemy[], int num_enemies, char **map) ;

void player_combat(player player, Enemy enemy[], int num_enemies, char **map);


#endif 