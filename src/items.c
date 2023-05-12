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

void create_flashlight(int max_x,int max_y, char **map){
    srand(time(0));
    int x = rand() % (LENGTH - 2) ; 
    int y = rand() % (HEIGHT - 2) ;
    if (map[x][y] == empty) {
        map[x][y] = flashlight;
    }
}


void remove_flashlight(int max_x,int max_y, char **map){
    for (int y=0; y<HEIGHT; y++){
        for (int x=0; x<LENGTH; x++){
            if (map[x][y] == flashlight) {
                map[x][y] = empty;
            }
        }
    }
}