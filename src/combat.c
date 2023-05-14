#include <string.h>
#include <unistd.h>
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
#include "../include/opponents.h"
#include "../include/combat.h"


void player_combat(player player, Enemy enemy[], int num_enemies, char **map)
{   
    for(int i=0 ;i <num_enemies;i++){
        if(enemy[i].health>0){
            int distance = sqrt(pow(enemy[i].pos.y - player.pos.y, 2) + pow(enemy[i].pos.x - player.pos.x, 2));
            
            if(distance<=player.inventory.armas.range){
                enemy[i].health-=player.inventory.armas.damage;
                
                if(enemy[i].health<=0){
                    map[enemy[i].pos.x][enemy[i].pos.y]=empty;
                    enemy[i].pos.x=-1;
                    enemy[i].pos.y=-1;
                    
                }
            }
        }
    }
}

void enemy_combat(player player, Enemy enemy[], int num_enemies, char **map) 
{
    for (int i = 0; i < num_enemies; i++) {
        if (whats_around(enemy[i].pos, map) == 2) {
            player.health -= enemy[i].attack;
            sleep(3);
            if (player.health <= 0) {
                endwin();
                printf("You died\n");  // é preciso melhorar isto para o jogo não acabar assim
                exit(0);
            }
        }

    }
}





