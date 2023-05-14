#include <string.h>
#include <stdbool.h>
#include <alloca.h>
#include <unistd.h>
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
#include "../include/combat.h"



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

player inicializa_player(player new_player){
    new_player.health=100;
    
    new_player.inventory.flashlight.collected=0;
    new_player.inventory.flashlight.radius=4;

    new_player.inventory.armas.collected=1;
    new_player.inventory.armas.damage=25;
    new_player.inventory.armas.speed=2.5;
    new_player.inventory.armas.range=2;

    return new_player;
}









void move_player(player player, Enemy *Enemy_array, int num_enemies, int max_x, int max_y, char **map){
    Position pos_item;
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
                if (whats_around(player.pos,map)==3) {
                    pos_item=collected(player.pos,map);
                    

                        // player.inventory.flashlight.collected=1;
                        // player.inventory.flashlight.radius=7;

                    if (map[pos_item.x][pos_item.y]==Flashlight) {
                        player.inventory.flashlight.collected=1;
                        player.inventory.flashlight.radius=7;
                    }
                    else if (map[pos_item.x][pos_item.y]==axe_char) {
                        player.inventory.armas.collected=1;
                        player.inventory.armas.damage=35;
                        player.inventory.armas.speed=3.25;
                        player.inventory.armas.range=3;
                    }
                    else if (map[pos_item.x][pos_item.y]==spear_char) {
                        player.inventory.armas.collected=1;
                        player.inventory.armas.damage=20;
                        player.inventory.armas.speed=1.5;
                        player.inventory.armas.range=4;
                    }
                    remove_item(pos_item,map);
                }
                

                break;
            case 'l':   //vê mapa todo
                
                if (player.inventory.flashlight.radius==7 || player.inventory.flashlight.radius==4){
                    player.inventory.flashlight.radius=1000;
                    
                }
                else if (player.inventory.flashlight.collected==1){
                    player.inventory.flashlight.radius=7;
                }else{
                    player.inventory.flashlight.radius=4;
                }
                break;
            case ' ':   //atacar

                player_combat(player,Enemy_array,num_enemies,map);
                //sleep(player.inventory.armas.speed);          

          

                break;
            case 'q':
                endwin();
                exit(0);
                break;
        }
        move_enemy(player, Enemy_array, num_enemies, map);
        print_map(player,Enemy_array,num_enemies,max_x,max_y,map);
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
