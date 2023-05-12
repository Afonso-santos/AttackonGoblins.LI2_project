#ifndef _ESTRUTURAS_H_
#define _ESTRUTURAS_H_

#include <stdbool.h>
#include <alloca.h>
#include <string.h>
#include <curses.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>





#define HEIGHT (max_y-7)
#define LENGTH (max_x-58)
#define player_char '@'
#define edge '#'
#define boox '='
#define empty '.'
#define obstacle '+'
#define flashlight 'F'
#define Shapes 3
// #define SIZE 5

typedef enum { TRIANGLE, SQUARE, CIRCLE } Shape;

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct inventory{
    //armas
    int flashlight_radius;
}inventory;

typedef struct Player{
    Position pos ;
    inventory inventory;
    //int health;    
    //int attack;
}player;

#endif 