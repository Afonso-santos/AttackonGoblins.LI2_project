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
#include "../include/menu.h"


void define(int *max_x, int *max_y) {
    initscr();

    // Obtém as dimensões da tela
    *max_y = getmaxy(stdscr);
    *max_x = getmaxx(stdscr);
}

void create_edge(int max_x,int max_y, char **map){
    srand(time(0));

    int num_obstacles = rand() % 11 + 37
; 

    for (int i = 0; i < num_obstacles; i++) {
        int shape = rand() % 3; // Gere um tipo de forma aleatório (0 a 2)
        Position pos;
        pos.x = rand() % (LENGTH - 2);
        pos.y = rand() % (HEIGHT - 2);

        switch (shape) {
            case TRIANGLE:
                create_Triangle(pos, max_x, max_y, map);
                break;
            case SQUARE:
                create_Square(pos, max_x, max_y, map);
                break;
            case CIRCLE:
                create_Circle(pos, max_x, max_y, map);
                break;
            default:
                break;
        }
    }
}

void create_map(int max_x,int max_y, char **map){
    for (int i =0; i<HEIGHT; i++) {
        for (int j =0;j<LENGTH; j++) {
            if (j==0 ||j==LENGTH-1 || i==0||i==HEIGHT-1) {

                map[j][i]=edge;

            }else{
                map[j][i]=empty;
            }   

        }

    }
}

void print_map(player player,Enemy *enemy, int num_enemies,int max_x,int max_y, char **map){   
    clear();
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < LENGTH; x++) {

            int distance = sqrt(pow(y - player.pos.y, 2) + pow(x - player.pos.x, 2));
            
            if (y == 0 || y == HEIGHT-1 || x == 0 || x == LENGTH-1) {
                // Print walls
                attron(COLOR_PAIR(4)); 
                mvprintw(y, x, "%c", map[x][y]); 
                attroff(COLOR_PAIR(4)); 

            } else if (distance < player.inventory.flashlight.radius) {
                // Print visible cells
                if (map[x][y] == empty) {
                    // Print empty cell
                    attron(COLOR_PAIR(3)); 
                    mvprintw(y, x, "%c", map[x][y]); 
                    attroff(COLOR_PAIR(3)); 
                } else if (map[x][y] == boox) {
                    // Print box
                    attron(COLOR_PAIR(6)); 
                    mvprintw(y, x, "%c", map[x][y]); 
                    attroff(COLOR_PAIR(6)); 

                } else if (map[x][y] == Flashlight || map[x][y] == axe_char || map[x][y] == spear_char || map[x][y] == swoord_char) {
                    // Print flashlight
                    attron(COLOR_PAIR(9)); 
                    mvprintw(y, x, "%c", map[x][y]); 
                    attroff(COLOR_PAIR(9)); 
                
                } else if (map[x][y] == enemy_char) {
                    // Print enemy
                    bool enemy_present = false;
                    for (int i = 0; i < num_enemies; i++) {
                        if (enemy[i].health && enemy[i].pos.x == x && enemy[i].pos.y == y) {

                            attron(COLOR_PAIR(7)); 
                            mvprintw(y, x, "%c", enemy_char); 
                            attroff(COLOR_PAIR(7)); 
                            enemy_present = true;
                            break;
                        }
                    }
                    if (!enemy_present) {
                        attron(COLOR_PAIR(7)); 
                        mvprintw(y, x, "%c", map[x][y]); 
                        attroff(COLOR_PAIR(7));  
                    }
                } else {
                    // Print other characters
                    attron(COLOR_PAIR(1)); 
                    mvprintw(y, x, "%c", map[x][y]); 
                    attroff(COLOR_PAIR(1));                   
                }
            } 
        }
    }
    start_color();
    init_pair(COR_TEXTO2, COLOR_RED, COLOR_BLACK);
    mvprintw(HEIGHT/2, LENGTH+5, "Player Health:");
    attron(COLOR_PAIR(COR_TEXTO2));
    mvprintw(HEIGHT/2, LENGTH+20, "%d", player.health);
    attroff(COLOR_PAIR(COR_TEXTO2));
    mvprintw((HEIGHT/2)+2, LENGTH+5, "Current weapon:");
    attron(COLOR_PAIR(COR_TEXTO2));
    mvprintw((HEIGHT/2)+2, LENGTH+21, "%s", player.inventory.armas.name);
    attroff(COLOR_PAIR(COR_TEXTO2));
    if (player.inventory.flashlight.collected == 1){
        mvprintw((HEIGHT/2)+4, LENGTH+5, "Flashlight collected:");
        attron(COLOR_PAIR(COR_TEXTO2));
        mvprintw((HEIGHT/2)+4, LENGTH+27, "YES");
        attroff(COLOR_PAIR(COR_TEXTO2));
    }
    else{
        mvprintw((HEIGHT/2)+4, LENGTH+5, "Flashlight collected:");
        attron(COLOR_PAIR(COR_TEXTO2));
        mvprintw((HEIGHT/2)+4, LENGTH+27, "NO");
        attroff(COLOR_PAIR(COR_TEXTO2));
    }
    mvprintw(player.pos.y, player.pos.x, "%c", player_char);
}



void free_map(int max_x, char **map) {
    // Libera memória alocada para o mapa
    for (int i = 0; i < max_x; i++) {
        free(map[i]);
    }
    free(map);
}