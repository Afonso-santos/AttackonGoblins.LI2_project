#include <stdbool.h>
#include <alloca.h>
#include <string.h>
#include <curses.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/mapa.h"
#include "../include/player.h"
#include "../include/obstaculos.h"
#include "../include/estruturas.h"
#include "../include/items.h"



void create_Triangle(Position pos, int max_x,int max_y, char **map)
{
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE - i; j++) {

            if (check(pos.x+j,pos.y+i, max_x, max_y, map)) {

                map[pos.x + j][pos.y + i] = obstacle;
            }
            
        }
       
    }
}

void create_Square(Position pos, int max_x,int max_y, char **map)
{   
    for (int i=0; i<SIZE; i++) {
        for (int j=0;j<SIZE ; j++) {
            
            if (check(pos.x+j,pos.y+i, max_x, max_y, map)) {
                
                map[pos.x + j][pos.y + i] = obstacle;
            }
       }
    }

}

void create_Circle( Position pos, int max_x,int max_y, char **map)
{
    int x = 0;
    int y = SIZE;
    int d = 3 - 2 * SIZE;
    int density = SIZE+1; // Ajuste o valor de density para aumentar ou diminuir a density do círculo

    while (x <= y) {
        for (int i = 0; i < density; i++) {
            if (check(pos.x+x,pos.y+y-i, max_x, max_y, map)) {
                map[pos.x + x][pos.y + y - i] = obstacle;
            }
            if (check(pos.x-x,pos.y+y-i, max_x, max_y, map)) {
                map[pos.x - x][pos.y + y - i] = obstacle;
            }
            if (check(pos.x+x,pos.y-y+i,max_x, max_y,  map)) {
                map[pos.x + x][pos.y - y + i] = obstacle;
            }
            if (check(pos.x-x,pos.y-y+i,max_x, max_y, map)) {
                map[pos.x - x][pos.y - y + i] = obstacle;
            }
            if (check(pos.x+y-i,pos.y+x,max_x, max_y, map)) {
                map[pos.x + y - i][pos.y + x] = obstacle;
            }
            if (check(pos.x-y+i,pos.y+x,max_x, max_y, map)) {
                map[pos.x - y + i][pos.y + x] = obstacle;
            }
            if (check(pos.x+y-i,pos.y-x,max_x, max_y, map)) {
                map[pos.x + y - i][pos.y - x] = obstacle;
            }
            if (check(pos.x-y+i,pos.y-x,max_x, max_y, map)) {
                map[pos.x - y + i][pos.y - x] = obstacle;
            }
        }

        if (d <= 0) {
            d += 4 * x + 6;
        }
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}


void create_barrel(int max_x,int max_y, char **map)
{
    srand(time(0));
    int num_barris = rand() % 16 +35; 

    for (int i = 0; i < num_barris; i++) {
        int x = rand() % (LENGTH - 2) ; 
        int y = rand() % (HEIGHT - 2) ;

        if (map[x][y] == empty) {
            map[x][y] = boox;
        }
    }
}



