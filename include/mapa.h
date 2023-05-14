#ifndef _MAPA_H_
#define _MAPA_H_


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
// #pragma once

#define SIZE 5

// int max_x, max_y;
// char **map;
// int SIZE = 5;


void define (int *max_x,int *max_y);

void create_edge (int max_x,int max_y, char **map);

void create_map(int max_x,int max_y, char **map);

void print_map(player player, Enemy *enemy, int num_enemies,int max_x,int max_y, char **map);

void free_map(int max_x, char **map);

#endif