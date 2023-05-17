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


Position collected(player player, char **map) {
    Position pos_thing;
    pos_thing.x = -1;
    pos_thing.y = -1;

    for (int i = player.pos.x - 1; i <= player.pos.x + 1; i++) {
        for (int j = player.pos.y - 1; j <= player.pos.y + 1; j++) {
            if (i!=player.pos.x || j!=player.pos.y){
                if (map[i][j] == Flashlight || map[i][j] == axe_char || map[i][j] == spear_char || map[i][j] == enemy_char) {
                    pos_thing.x = i;
                    pos_thing.y = j;
                    return pos_thing;
                }
            }
        }
    }

    return pos_thing;
}


void remove_thing (Position pos, char **map){
    if(map[pos.x][pos.y]==Flashlight || map[pos.x][pos.y]==axe_char || map[pos.x][pos.y]==spear_char || map[pos.x][pos.y]==swoord_char || map[pos.x][pos.y]==enemy_char){
        map[pos.x][pos.y]=empty;
    }
}


int whats_around(player player, char **map) {
    for (int i = player.pos.x - 1; i <= player.pos.x + 1; i++) {
        for (int j = player.pos.y - 1; j <= player.pos.y + 1; j++) {
            if (i!=player.pos.x || j!=player.pos.y){
                if (map[i][j] == enemy_char) {
                    return 1;
                } else if (map[i][j] == player_char) {
                    return 2;
                } else if (map[i][j] == axe_char || map[i][j] == spear_char || map[i][j] == Flashlight) {
                    return 3;
                }
            }
        }
    }
    return 0;
}

// void remove_flashlight(int max_x,int max_y, char **map){
    // for (int y=0; y<HEIGHT; y++){
        // for (int x=0; x<LENGTH; x++){
            // if (map[x][y] == flashlight) {
                // map[x][y] = empty;
            // }
        // }
    // }
// }