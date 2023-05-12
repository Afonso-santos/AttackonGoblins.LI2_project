#include <string.h>
#include <stdbool.h>
#include <alloca.h>
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


int check(int x, int y,int max_x,int max_y, char **map) {
    if (x < 2 || x >= LENGTH - 2|| y < 2 || y >= HEIGHT - 2) {
        return 0;
    }
    if (map[x][y] != edge ) {
        return 1;
    } else {
        return 0;
    }
}


int check_player(int x, int y,int max_x,int max_y, char **map) {
    if (x <= 2 || x >= LENGTH - 2|| y <= 2 || y >= HEIGHT - 2) {
        return 0;
    }
    if (map[x][y] == empty && x>2 && x<LENGTH-2 && y>2 && y<HEIGHT-2) {
        
        return 1;
    } else {
        return 0;
    }
}

void move_player(player player, int max_x, int max_y, char **map){
    while(1){
        int direction = getch();
        switch (direction) {
            case 'w':  // Cima
                if (map[player.pos.x][player.pos.y-1] == empty ) {
                    player.pos.y--;
                }
                break;
            case 's':  // Baixo
                if (map[player.pos.x][player.pos.y+1] == empty) {
                    player.pos.y++;
                }
                break;
            case 'a':  // Esquerda
                if (map[player.pos.x-1][player.pos.y] == empty) {
                    player.pos.x--;
                }
                break;
            case 'd':  // Direita
                if (map[player.pos.x+1][player.pos.y] == empty) {
                    player.pos.x++;
                }
                break;
            case '7':  // Diagonal superior esquerda
                if (map[player.pos.x-1][player.pos.y-1] == empty) {
                    player.pos.x--;
                    player.pos.y--;
                }
                break;
            case '9':  // Diagonal superior direita
                if (map[player.pos.x+1][player.pos.y-1] == empty) {
                    player.pos.x++;
                    player.pos.y--;
                }
                break;
            case '1':  // Diagonal inferior esquerda
                if (map[player.pos.x-1][player.pos.y+1] == empty) {
                    player.pos.x--;
                    player.pos.y++;
                }
                break;
            case '3':  // Diagonal inferior direita
                if (map[player.pos.x+1][player.pos.y+1] == empty) {
                    player.pos.x++;
                    player.pos.y++;
                }
                break;
            case 'f':  // apanhar lanterna
                if (map[player.pos.x][player.pos.y-1]==flashlight || map[player.pos.x][player.pos.y+1]==flashlight || map[player.pos.x-1][player.pos.y]==flashlight || map[player.pos.x+1][player.pos.y]==flashlight || map[player.pos.x-1][player.pos.y-1]==flashlight || map[player.pos.x+1][player.pos.y-1]==flashlight || map[player.pos.x-1][player.pos.y+1]==flashlight || map[player.pos.x+1][player.pos.y+1]==flashlight) {
                    remove_flashlight(max_x,max_y, map);
                    player.inventory.flashlight_radius=7;
                }
                break;
            case 'l':   //vê mapa todo
                if (player.inventory.flashlight_radius==7 || player.inventory.flashlight_radius==4){
                    player.inventory.flashlight_radius=1000;
                }
                else if (player.inventory.flashlight_radius==1000){
                    player.inventory.flashlight_radius=4;
                }
                break;
            case 'q':
                endwin();
                exit(0);
                break;
        }
        
        print_map(player, max_x, max_y, map);
    }
}

player create_coordinates(int max_x,int max_y, char **map) {
    player new_player;
    srand(time(NULL));
    while (check_player(new_player.pos.x, new_player.pos.y,max_x,max_y, map) != 1){
        new_player.pos.x = (rand() % (LENGTH - 2));
        new_player.pos.y = (rand() % (HEIGHT - 2));
    }
    return new_player;
}
