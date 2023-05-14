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
#include "../include/opponents.h"

void create_flashlight(int max_x,int max_y, char **map){

    srand(time(0));
    Position pos;
    pos.x=-2;
    pos.y=-2;

    while (check_player(pos.x,pos.y,max_x,max_y,map) != 1){
        pos.x = (rand() % (LENGTH - 2));
        pos.y = (rand() % (HEIGHT - 2));
    }
    map[pos.x][pos.y] = Flashlight;
}

void creat_guns(int max_x,int max_y, char **map){
    srand(time(0));
    Position pos;
    pos.x=-2;
    pos.y=-2;
    int gun = rand() % 2;

    if (gun == 0){
        while (check_player(pos.x, pos.y,max_x,max_y,map) != 1){
            pos.x = (rand() % (LENGTH - 2));
            pos.y = (rand() % (HEIGHT - 2));
        }
        map[pos.x][pos.y] = axe_char;
    }else if (gun == 1){
        while (check_player(pos.x, pos.y,max_x,max_y,map) != 1){
            pos.x = (rand() % (LENGTH - 2));
            pos.y = (rand() % (HEIGHT - 2));
        }
        map[pos.x][pos.y] = spear_char;
    }
}


Position collected(Position pos, char **map){
    Position pos_item;
    
    for (int i = -1; i <2 ; i++){
        for (int j = -1; j <2 ; j++){
            
            if (map[pos.x+i][pos.y+j]==Flashlight || map[pos.x+i][pos.y+j]==axe_char || map[pos.x+i][pos.y+j]==spear_char ) {
                pos_item.x=pos.x+i;
                pos_item.y=pos.y+j;
                
                return pos_item;
            }
        }
    }
    pos_item.x=-1;
    pos_item.y=-1;
    return pos_item;
}


void remove_item (Position pos, char **map){
    if(map[pos.x][pos.y]==Flashlight || map[pos.x][pos.y]==axe_char || map[pos.x][pos.y]==spear_char || map[pos.x][pos.y]==swoord_char){
        map[pos.x][pos.y]=empty;
    }
}


int whats_around(Position pos, char **map) {
    for (int i = pos.x - 1; i <= pos.x + 1; i++) {
        for (int j = pos.y - 1; j <= pos.y + 1; j++) {
            if (map[i][j] == enemy_char) {
                return 1;
            } else if (map[i][j] == player_char) {
                return 2;
            } else if (map[i][j] == axe_char || map[i][j] == spear_char || map[i][j] == Flashlight) {
                return 3;
            }
        }
    }
    return 0;
}