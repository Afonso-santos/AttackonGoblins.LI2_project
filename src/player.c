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
#include "../include/menu.h"


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
    new_player.inventory.armas.collected=0;
    strcpy(new_player.inventory.armas.name, "SWORD");

    return new_player;
}

int enemy_active (Enemy *Enemy_array, int num_enemies){
    for (int i = 0; i < num_enemies; i++){
        if (Enemy_array[i].active==1) return 1;
    }
    return 0;
}


void move_player(player player, Enemy *Enemy_array, int num_enemies, int max_x, int max_y, char **map){
    Position pos_thing;
    int inimigos_ativos = 1;
    while(player.health>0 && inimigos_ativos==1){
        int direction = getch();
        switch (direction) {
            case 'w':  // Cima
                if (map[player.pos.x][player.pos.y-1] == empty ) {
                    player.pos.y--;
                }
                break;
            case '8':  // Cima
                if (map[player.pos.x][player.pos.y-1] == empty ) {
                    player.pos.y--;
                }
                break;  
            case 's':  // Baixo
                if (map[player.pos.x][player.pos.y+1] == empty) {
                    player.pos.y++;
                }
                break;
            case '2':  // Baixo
                if (map[player.pos.x][player.pos.y+1] == empty) {
                    player.pos.y++;
                }
                break;
            case 'a':  // Esquerda
                if (map[player.pos.x-1][player.pos.y] == empty) {
                    player.pos.x--;
                }
                break;
            case '4':  // Esquerda
                if (map[player.pos.x-1][player.pos.y] == empty) {
                    player.pos.x--;
                }
                break;
            case 'd':  // Direita
                if (map[player.pos.x+1][player.pos.y] == empty) {
                    player.pos.x++;
                }
                break;
            case '6':  // Direita
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
            case 'f':  // apanhar item
                if (whats_around(player,map)==3) {
                    pos_thing=collected(player,map);
                    if (map[pos_thing.x][pos_thing.y]==Flashlight) {
                        player.inventory.flashlight.collected=1;
                        player.inventory.flashlight.radius=7;
                    }
                    else if (map[pos_thing.x][pos_thing.y]==axe_char){
                        strcpy(player.inventory.armas.name, "AXE");;
                        player.inventory.armas.collected=1;
                    }
                    else if (map[pos_thing.x][pos_thing.y]==spear_char){
                        strcpy(player.inventory.armas.name, "SPEAR");;
                        player.inventory.armas.collected=1;
                    }

                    remove_thing(pos_thing,map);
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
            case 32:   //atacar   (o 32 é o código ASCII da tecla "space")
                if (whats_around(player, map) == 1) {
                    pos_thing = collected(player, map);
                    if (map[pos_thing.x][pos_thing.y] == enemy_char) {
                        for (int i = 0; i < num_enemies; i++) {
                            if (Enemy_array[i].pos.x == pos_thing.x && Enemy_array[i].pos.y == pos_thing.y && Enemy_array[i].health==50) {
                                Enemy_array[i].health = 0;
                                Enemy_array[i].active = 0; // Definir o inimigo como inativo
                                remove_thing(pos_thing, map);
                                break;
                            }
                            else if (Enemy_array[i].pos.x == pos_thing.x && Enemy_array[i].pos.y == pos_thing.y && Enemy_array[i].health==100 && player.inventory.armas.collected==1){  //se tiver uma arma ele mata com um hit
                                Enemy_array[i].health = 0;
                                Enemy_array[i].active = 0; // Definir o inimigo como inativo
                                remove_thing(pos_thing, map);
                                break;
                            }
                            else if (Enemy_array[i].pos.x == pos_thing.x && Enemy_array[i].pos.y == pos_thing.y && Enemy_array[i].health==100 && player.inventory.armas.collected==0){   //se não tiver arma mata com dois hits
                                Enemy_array[i].health = 50;
                            }
                        }
                    }
                }   
                break;
            case 'q':
                endwin();
                exit(0);
                break;
        }
        if (whats_around(player, map) == 1 && direction!=32) {       //o mob só ataca caso o jogador não o ataque
            player.health = player.health - Enemy_array[2].attack;
        }
        print_map(player,Enemy_array,num_enemies,max_x,max_y,map);
        move_enemy(player, Enemy_array, num_enemies, map);
        print_map(player,Enemy_array,num_enemies,max_x,max_y,map);
        inimigos_ativos = enemy_active(Enemy_array, num_enemies);
    }
    if (player.health<=0) game_over();
    else you_win();
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