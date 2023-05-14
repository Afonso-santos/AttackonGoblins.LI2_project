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
#define enemy_char 'G'
#define axe_char 'T'
#define spear_char  '!'
#define swoord_char '1'
#define Shapes 3
// #define SIZE 5

typedef enum { TRIANGLE, SQUARE, CIRCLE } Shape;

typedef struct Position {
    int x;
    int y;
} Position;



typedef struct armas {
    int collected;
    int damage;  // = 25
    float speed; // = 2.5
    int range;
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
    int health;    
    
}player;

typedef struct Enemy{
    Position pos;
    int health;
    int attack;
}Enemy;

#endif 