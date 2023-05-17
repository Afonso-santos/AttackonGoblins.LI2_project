#include <stdbool.h>
#include <alloca.h>
#include <string.h>
#include <curses.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../include/mapa.h"
#include "../include/player.h"
#include "../include/obstaculos.h"
#include "../include/estruturas.h"
#include "../include/items.h"
#include "../include/opponents.h"
#include "../include/menu.h"


// função que abre a tela de jogo
void abrir_jogo() {
  timeout(1*1000);
  clear();
  int max_x, max_y;
  define(&max_x, &max_y);
  #define HEIGHT (max_y-7)
  #define LENGTH (max_x-58)       
// 
  char **map = calloc(LENGTH, sizeof(char *));
  for (int i = 0; i < LENGTH; i++) {
      map[i] = calloc(HEIGHT, sizeof(char));
  }
// 
  create_map(max_x, max_y, map);
  create_edge(max_x, max_y, map);
  create_barrel(max_x, max_y, map);
  create_flashlight(max_x, max_y, map);
  creat_guns(max_x, max_y, map);

  player new_player = create_coordinates(max_x, max_y, map);
  new_player =inicializa_player(new_player);
  
  int numberOfEnemies;
  
  Enemy* enemy_array = creat_enemies(&numberOfEnemies, max_x, max_y, map);
  print_map(new_player, enemy_array, numberOfEnemies, max_x, max_y, map);
  move_player(new_player, enemy_array, numberOfEnemies, max_x, max_y, map);

  getch(); // Aguarda pressionar uma tecla para sair

  
  free_map(max_x, map);       
  free(enemy_array);
}


// função que abre a tela de ajuda
void ajuda() {
  clear();
  start_color();
  init_pair(COR_TEXTO, COLOR_BLUE, COLOR_BLACK);
  init_pair(COR_TEXTO2, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(COR_TEXTO));
  printw("Help:\n\n\n");
  attroff(COLOR_PAIR(COR_TEXTO));
  printw(" ----------------------\n");
  printw("|1 -> ");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("Goal of the game ");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  printw("|2 -> ");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("Commands         ");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  printw("|3 -> ");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("Back to main menu");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  printw(" ----------------------\n");
  refresh();
  int opcao_selecionada = getch();
  switch (opcao_selecionada) {
    case '1':
      clear();
      init_pair(COR_TEXTO3, COLOR_GREEN, COLOR_BLACK);
      init_pair(COR_TEXTO4, COLOR_YELLOW, COLOR_BLACK);
      attron(COLOR_PAIR(COR_TEXTO3));
      printw("Game instructions:\n\n\n");
      attroff(COLOR_PAIR(COR_TEXTO2));
      printw("-The main objective in this game is to kill all the mobs in the room you are currently in.\n");
      printw("-Initially the player has a sword and it is necessary to hit the mob twice to kill it. But if you pick up a spear or an axe you can kill them with a single hit.\n");
      printw("-The game will end once you've killed all mobs in all existing rooms.\n");
      printw("-And don't forget to be careful when facing the mobs so you don't have to reset all your progress.\n\n");
      attron(COLOR_PAIR(COR_TEXTO4));
      printw("Good luck!");
      attroff(COLOR_PAIR(COR_TEXTO4));
      refresh();
      getch();   
      break;           //volta para o menu de ajuda mal alguma tecla seja pressionada
    case '2':
      clear();
      init_pair(COR_TEXTO, COLOR_BLUE, COLOR_BLACK);
      init_pair(COR_TEXTO3, COLOR_GREEN, COLOR_BLACK);
      attron(COLOR_PAIR(COR_TEXTO3));
      printw("Game Commands:\n\n\n");
      attroff(COLOR_PAIR(COR_TEXTO3));
      printw("You'll need to use these keys to play:\n\n");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("         8");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->up                            ");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("2");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->down\n");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("         4");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->left                          ");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("6");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->right\n");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("         7");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->top left diagonal");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("             9");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->top right diagonal\n");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("         1");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->bottom left diagonal");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("          3");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->bottom right diagonal\n");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("         f");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->catch item");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("                    l");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->total light on map (on/off)\n");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("         space");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->atack");
      attron(COLOR_PAIR(COR_TEXTO));
      printw("                     q");
      attroff(COLOR_PAIR(COR_TEXTO));
      printw("->close the game\n");
      refresh();
      getch();
      break;           //volta para o menu de ajuda mal alguma tecla seja pressionada
    case '3':
      break;           //volta para o menu de ajuda mal alguma tecla seja pressionada
  }
}

// função que abre a tela de créditos
void creditos() {
  clear();
  start_color();
  init_pair(COR_TEXTO, COLOR_BLUE, COLOR_BLACK);
  init_pair(COR_TEXTO2, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(COR_TEXTO));
  printw("Credits:\n\n\n");
  attroff(COLOR_PAIR(COR_TEXTO));
  printw("This game was made by:\n");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("                            ->");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("Afonso Pimenta (a100648)\n");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("                            ->");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("Afonso Santos (a104276)\n");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("                            ->");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("Gonçalo Costa (a100824)\n");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("                            ->");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("Gonçalo Cruz (a104346)\n\n\n\n\n\n");
  for (int k=0; k<(COLS-24)/2; k++) printw(" ");    //o "24" corresponde ao tamanho do printw
  printw(" ------------------------\n");
  for (int k=(COLS-25)/2+25; k<COLS; k++) printw(" ");
  printw("|");
  attron(COLOR_PAIR(COR_TEXTO2));
  printw("1 -> Return to main menu");
  attroff(COLOR_PAIR(COR_TEXTO2));
  printw("|\n");
  for (int k=0; k<(COLS-24)/2; k++) printw(" ");
  printw(" ------------------------\n");
  for (int k=(COLS-24)/2+24; k<COLS; k++) printw(" ");
  refresh();
  int opcao_selecionada = getch();
  switch (opcao_selecionada) {
    case '1':
      break;
  }
}


// função que abre a tela de you win
void you_win(){
  clear();
  start_color();
  init_pair(COR_TEXTO3, COLOR_GREEN, COLOR_BLACK);
  attron(COLOR_PAIR(COR_TEXTO3));
  attron(A_BOLD);       //para imprimir a frase a negrito
  for (int k=0; k<LINES/2; k++) printw("\n");
  for (int k=0; k<(COLS-8)/2; k++) printw(" ");
  printw ("You win!\n");
  for (int k=0; k<(COLS-8)/2; k++) printw(" ");
  printw ("Congrats");
  attroff(A_BOLD);
  attroff(COLOR_PAIR(COR_TEXTO3));
  refresh();
  sleep(3);
  flushinp();     //ignora todas as teclas pressionadas
}


// função que abre a tela de game over
void game_over(){
  clear();
  start_color();
  attron(COLOR_PAIR(COR_TEXTO2));
  attron(A_BOLD);       //para imprimir a frase a negrito
  for (int k=0; k<LINES/2; k++) printw("\n");
  for (int k=0; k<(COLS-9)/2; k++) printw(" ");
  printw ("Game Over");
  attroff(A_BOLD);
  attroff(COLOR_PAIR(COR_TEXTO2));
  refresh();
  sleep(3);
  flushinp();       //ignora todas as teclas pressionadas
}


// função que fecha o programa
void sair() {
  endwin();
  exit(0);
}


void create_menu(){
    // cria as opções do menu
  opcao_menu opcoes[] = {
      {"New Game", abrir_jogo},          
      {"Help", ajuda},
      {"Credits", creditos},
      {"Leave", sair},
  };

  // variável que armazena a opção selecionada
  int opcao_atual = 0;

  // loop do menu
  while (1) {
    clear();
    for (int j = 0; j < 5; j++) {
        attron(COLOR_PAIR(COR_TEXTO2));  // Ativar a cor de fundo definida pelo par de cores especificado
        if (j == 2) {
            for (int k=0; k<(COLS-77)/2; k++) printw(" ");
            printw(" _____      _____     _____            _____          _______  _______  _____\n");
            for (int k=0; k<(COLS-77)/2; k++) printw(" ");
            printw("|     |    /     \\   /     \\ |      | |       |          |        |    |\n");
            for (int k=0; k<(COLS-77)/2; k++) printw(" ");
            printw("|     |   |       | |        |      | |       |          |        |    |\n");
            for (int k=0; k<(COLS-77)/2; k++) printw(" ");
            printw("|_____|   |       | |   ___  |      | |_____  |          |        |    |_____\n");
            for (int k=0; k<(COLS-77)/2; k++) printw(" ");
            printw("|     \\   |       | |  |_  | |      | |       |          |        |    |\n");
            for (int k=0; k<(COLS-77)/2; k++) printw(" ");
            printw("|      \\  |       | |      | |      | |       |          |        |    |\n");
            for (int k=0; k<(COLS-77)/2; k++) printw(" ");
            printw("|       \\  \\_____/   \\_____| |______| |_____  |_____  ___|___     |    |_____\n");
            attroff(COLOR_PAIR(COR_TEXTO2));
        }
        else {
            for (int i = 0; i < COLS; i++) {
                printw(" ");
            }
        }
    }
    printw("\n\n");


    // imprime as opções do menu
    for (int i=0; i<4; i++) {
      if (i==opcao_atual){
        attron(COLOR_PAIR(COR_TEXTO2));
        printw("* %s *", opcoes[i].titulo);
        attroff(COLOR_PAIR(COR_TEXTO2));
      } else {
        attron(COLOR_PAIR(COR_TEXTO));
        printw("  %s  ", opcoes[i].titulo);
        attroff(COLOR_PAIR(COR_TEXTO));
      }
      printw("\n");
    }
    refresh();

    // seleção do jogador
    int tecla = getch();
    switch (tecla) {
      case 65:    //Código ASCII para seta para cima
        opcao_atual--;
        if (opcao_atual < 0) {
          opcao_atual = 3;
        }
        break;
      case 66:     //Código ASCII para seta para baixo
        opcao_atual++;
        if (opcao_atual > 3) {
          opcao_atual = 0;
        }
        break;
      case '\n':   //seleciona a opção desejada
        opcoes[opcao_atual].acao();
        break;
    }
  }
}