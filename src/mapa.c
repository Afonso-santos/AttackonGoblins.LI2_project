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


void define(int *max_x, int *max_y) {
    initscr();

    // Obtém as dimensões da tela
    *max_y = getmaxy(stdscr);
    *max_x = getmaxx(stdscr);

    // map = malloc(sizeof(char*) * (*max_x));
    // for (int i = 0; i < (*max_x); i++) {
        // map[i] = malloc(sizeof(char) * (*max_y));
    // }
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

void print_map(player player,int max_x,int max_y, char **map){   
    clear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < LENGTH; x++) {
            int distance = sqrt(pow(y - player.pos.y, 2) + pow(x - player.pos.x, 2));
            
            if (y==0 ||y==HEIGHT-1 ||x==0 ||x==LENGTH-1 ) {
                
                attron(COLOR_PAIR(4)); // set color
                mvprintw(y,x ,"%c" ,map[x][y]); // print cell
                attroff( COLOR_PAIR(4)); // unset color
                            
            }else if (distance < player.inventory.flashlight_radius) {

                if (map[x][y]==empty) {

                    attron(COLOR_PAIR(3)); // set color
                    mvprintw(y,x ,"%c" ,map[x][y]); // print cell
                    attroff( COLOR_PAIR(3)); // unset color

                }else if (map[x][y]==boox) {
                    
                    attron(COLOR_PAIR(6)); // set color
                    mvprintw(y,x ,"%c" ,map[x][y]); // print cell
                    attroff( COLOR_PAIR(6)); // unset color
                }else if (map[x][y]==flashlight) {  
                    attron(COLOR_PAIR(7)); // set color
                    mvprintw(y,x ,"%c" ,map[x][y]); // print cell
                    attroff( COLOR_PAIR(7)); // unset color
                }
                else {

                    attron(COLOR_PAIR(1)); // set color
                    mvprintw(y,x ,"%c" ,map[x][y]); // print cell
                    attroff( COLOR_PAIR(1)); // unset color                   
                }
            } 
        }
    }
    mvprintw(player.pos.y,player.pos.x,"%c",player_char);
}

void free_map(int max_x, char **map) {
    // Libera memória alocada para o map
    for (int i = 0; i < max_x; i++) {
        free(map[i]);
    }
    free(map);
}









