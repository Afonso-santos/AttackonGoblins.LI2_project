
#include <string.h>
#include <stdbool.h>
#include <alloca.h>
#include <curses.h>
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
#include "../include/combat.h"





void move_enemy(player player, Enemy enemy[], int num_enemies, char **map) { 
    
    for (int i = 0; i < num_enemies; i++) {
        
        
        int distance = sqrt(pow(enemy[i].pos.y - player.pos.y, 2) + pow(enemy[i].pos.x - player.pos.x, 2));
          
        
        if(enemy[i].health>0){


          
            if (distance<=player.inventory.flashlight.radius+1) {

                //enemy_combat(player,enemy,num_enemies,map);

                if (enemy[i].pos.x < player.pos.x) {
                    if (map[enemy[i].pos.x + 1][enemy[i].pos.y] == empty) {
                        map[enemy[i].pos.x][enemy[i].pos.y] = empty;
                        enemy[i].pos.x++;
                        map[enemy[i].pos.x][enemy[i].pos.y] = enemy_char;
                    }
                } else if (enemy[i].pos.x > player.pos.x) {
                    if (map[enemy[i].pos.x - 1][enemy[i].pos.y] == empty) {
                        map[enemy[i].pos.x][enemy[i].pos.y] = empty;
                        enemy[i].pos.x--;
                        map[enemy[i].pos.x][enemy[i].pos.y] = enemy_char;
                    }
                } else if (enemy[i].pos.y < player.pos.y) {
                    if (map[enemy[i].pos.x][enemy[i].pos.y + 1] == empty) {
                        map[enemy[i].pos.x][enemy[i].pos.y] = empty;
                        enemy[i].pos.y++;
                        map[enemy[i].pos.x][enemy[i].pos.y] = enemy_char;
                    }
                } else if (enemy[i].pos.y > player.pos.y) {
                    if (map[enemy[i].pos.x][enemy[i].pos.y - 1] == empty) {
                        map[enemy[i].pos.x][enemy[i].pos.y] = empty;
                        enemy[i].pos.y--;
                        map[enemy[i].pos.x][enemy[i].pos.y] = enemy_char;
                    }
                }


            }else{
                int dx = rand() % 3 - 1; 
                int dy = rand() % 3 - 1; 
                if (map[enemy[i].pos.x + dx][enemy[i].pos.y + dy] == empty) { 
                    map[enemy[i].pos.x][enemy[i].pos.y] = empty; 
                    enemy[i].pos.x += dx; 
                    enemy[i].pos.y += dy;
                    map[enemy[i].pos.x][enemy[i].pos.y] = enemy_char;   
                }
            }            
        }
    }
}



Enemy* creat_enemies(int*number_enemies, int max_x, int max_y, char **map) {
    srand(time(NULL));
    int num_enemies = rand() % 6 + 10;
    Enemy* enemy_array = malloc(num_enemies * sizeof(Enemy));
    for (int i = 0; i < num_enemies; i++) {
        // Initialize the position to an invalid value
        Enemy new_enemy;
        new_enemy.pos.x = -1;
        new_enemy.pos.y = -1;

        // Generate a random position that is not occupied by another enemy
        int pos_taken;
        do {
            pos_taken = 0;
            new_enemy.pos.x = rand() % (LENGTH - 2);
            new_enemy.pos.y = rand() % (HEIGHT - 2);
            for (int q = 0; q < i; q++) {
                if (enemy_array[q].pos.x == new_enemy.pos.x &&
                    enemy_array[q].pos.y == new_enemy.pos.y) {
                    pos_taken = 1;
                    break;
                }
            }
        } while (check_player(new_enemy.pos.x, new_enemy.pos.y,max_x,max_y,map) != 1 || pos_taken == 1);


        // Set the enemy's health and attack
        new_enemy.health = 100;
        new_enemy.attack = 10;
        map[new_enemy.pos.x][new_enemy.pos.y] = enemy_char;
        enemy_array[i] = new_enemy;
    }
    *number_enemies = num_enemies;
    return enemy_array;
}

