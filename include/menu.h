#include <stdbool.h>
#include <alloca.h>
#include <string.h>
#include <curses.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/estruturas.h"

#define COR_FUNDO 8
#define COR_TEXTO 9        //letras azuis
#define COR_OPCAO 10
#define COR_TEXTO2 11     //letras vermelhas
#define COR_TEXTO3 12    //letras verdes
#define COR_TEXTO4 13    //letras amarelas
#define COR_TEXTO5 14
#define COR_TEXTO6 15

typedef struct {
  char* titulo;
  void (*acao)();
} opcao_menu;

void abrir_jogo();

void ajuda();

void creditos();

void you_win();

void game_over();

void sair();

void create_menu();

void player_health(player player, int max_x, int max_y);