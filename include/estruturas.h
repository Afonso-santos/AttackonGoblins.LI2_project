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
#define Flashlight 'F'
#define enemy_char 'E'
#define axe_char 'A'
#define spear_char  'P'
#define swoord_char 'S'
#define gun_char 'G'
#define medicKit 'K'
#define Shapes 3
// #define SIZE 5

typedef enum { TRIANGLE, SQUARE, CIRCLE } Shape;

typedef struct Position {
    int x;
    int y;
} Position;


typedef struct armas {
    int collected;
    char name[20];
} armas;


typedef struct flashlight {
    int collected;
    int radius;
} Flash;

typedef struct inventory{
    armas armas;
    Flash flashlight;
}inventory;

typedef struct Player{
    Position pos ;
    inventory inventory;
    unsigned int health;    
}player;

typedef struct Enemy{
    Position pos;
    unsigned int health;
    int attack;
    int active;
}Enemy;

#endif 