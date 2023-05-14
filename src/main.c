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
#include "../include/menu.h"

int main() {
    initscr(); // Inicializa a biblioteca ncurses
    curs_set(0);
          
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_color(COLOR_YELLOW, 941, 902, 549);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK); 
    init_color(COLOR_RED, 800, 400,0 );
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_WHITE);
    init_pair(9, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COR_FUNDO, COLOR_BLACK, COLOR_WHITE);
    init_pair(COR_TEXTO, COLOR_BLUE, COLOR_BLACK);
    init_pair(COR_OPCAO, COLOR_BLACK, COLOR_RED);
    init_pair(COR_TEXTO2, COLOR_RED, COLOR_BLACK);

    while (1){
        create_menu();
    }
   
    return 0;
}