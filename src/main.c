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

int main() {
    initscr(); // Inicializa a biblioteca ncurses
    curs_set(0);

    int max_x, max_y;
    define(&max_x, &max_y);
    #define HEIGHT (max_y-7)
    #define LENGTH (max_x-58)       

    char **map = calloc(LENGTH, sizeof(char *));
    for (int i = 0; i < LENGTH; i++) {
        map[i] = calloc(HEIGHT, sizeof(char));
    }
    

    
    
    start_color();
   
   
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_color(COLOR_YELLOW, 941, 902, 549);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK); 
    init_color(COLOR_RED, 800, 400,0 );
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);


    curs_set(0);

    create_map(max_x, max_y, map);
    create_edge(max_x, max_y, map);
    create_barrel(max_x, max_y, map);
    create_flashlight(max_x, max_y, map);

    player new_player = create_coordinates(max_x, max_y, map);
    new_player.inventory.flashlight_radius=4; // cria uma nova estrutura player com coordenadas aleatórias
    print_map(new_player,  max_x, max_y, map);
    move_player(new_player,  max_x,  max_y, map);

    getch(); // Aguarda pressionar uma tecla para sair

    endwin(); // Encerra o uso da biblioteca ncurses

    free_map(max_x, map);

    return 0;
}
