#include <curses.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int max_x, max_y;
char **mapa;

void define() {
    // Inicializa a biblioteca ncurses
    initscr();

    // Obtém as dimensões da tela
    max_y = getmaxy(stdscr);
    max_x = getmaxx(stdscr);

    mapa = malloc(sizeof(char*) * max_x);
    for (int i = 0; i < max_x; i++) {
        mapa[i] = malloc(sizeof(char) * max_y);
    }
}


// #define ALTURA  49
// #define COMPRIMENTO 180
#define ALTURA (max_y-7)
#define COMPRIMENTO (max_x-58)
    
#define player_char '@'
#define wall '#'
#define floor '#'
#define boox '='
#define empty ' '
#define parede '.'

// char mapa[COMPRIMENTO][ALTURA];
int tamanho = 5;

#define Shapes 3

typedef enum { TRIANGLE, SQUARE, CIRCLE } Shape;
typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Player{
    Position pos ;
    //int health;    
    //int attack;
}player;


int check(int x, int y) {
    if (x < 2 || x >= COMPRIMENTO - 2|| y < 2 || y >= ALTURA - 2) {
        return 0;
    }
    if (mapa[x][y] != wall && mapa[x][y] != floor) {
        return 1;
    } else {
        return 0;
    }
}



void gera_Triangle(int tamanho, Position pos)
{
    int i, j;
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho - i; j++) {

            if (check(pos.x+j,pos.y+i)) {

                mapa[pos.x + j][pos.y + i] = parede;
            }
            
        }
       
    }
}


void gera_Square(int tamanho,Position pos)
{   
    for (int i=0; i<tamanho; i++) {
        for (int j=0;j<tamanho ; j++) {
            
            if (check(pos.x+j,pos.y+i)) {
                
                mapa[pos.x + j][pos.y + i] = parede;
            }
       }
    }

}


//mapa[pos.x + x][pos.y + y - i]
void gera_Circle(int tamanho, Position pos)
{
    int x = 0;
    int y = tamanho;
    int d = 3 - 2 * tamanho;
    int densidade = 6; // Ajuste o valor de densidade para aumentar ou diminuir a densidade do círculo

    while (x <= y) {
        for (int i = 0; i < densidade; i++) {
            if (check(pos.x+x,pos.y+y-i)) {
                mapa[pos.x + x][pos.y + y - i] = parede;
            }
            if (check(pos.x-x,pos.y+y-i)) {
                mapa[pos.x - x][pos.y + y - i] = parede;
            }
            if (check(pos.x+x,pos.y-y+i)) {
                mapa[pos.x + x][pos.y - y + i] = parede;
            }
            if (check(pos.x-x,pos.y-y+i)) {
                mapa[pos.x - x][pos.y - y + i] = parede;
            }
            if (check(pos.x+y-i,pos.y+x)) {
                mapa[pos.x + y - i][pos.y + x] = parede;
            }
            if (check(pos.x-y+i,pos.y+x)) {
                mapa[pos.x - y + i][pos.y + x] = parede;
            }
            if (check(pos.x+y-i,pos.y-x)) {
                mapa[pos.x + y - i][pos.y - x] = parede;
            }
            if (check(pos.x-y+i,pos.y-x)) {
                mapa[pos.x - y + i][pos.y - x] = parede;
            }
        }

        if (d <= 0) {
            d += 4 * x + 6;
        }
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void gera_wall()
{
    srand(time(0));

    int num_paredes = rand() % 11 + 37
; 

    for (int i = 0; i < num_paredes; i++) {
        int shape = rand() % 3; // Gere um tipo de forma aleatório (0 a 2)
        Position pos;
        pos.x = rand() % (COMPRIMENTO - 2);
        pos.y = rand() % (ALTURA - 2);

        switch (shape) {
            case TRIANGLE:
                gera_Triangle(tamanho, pos);
                break;
            case SQUARE:
                gera_Square(tamanho, pos);
                break;
            case CIRCLE:
                gera_Circle(tamanho, pos);
                break;
            default:
                break;
        }
    }
}


void gera_barril()
{
    srand(time(0));
    int num_barris = rand() % 16 +35; 

    for (int i = 0; i < num_barris; i++) {
        int x = rand() % (COMPRIMENTO - 2) ; 
        int y = rand() % (ALTURA - 2) ;

        if (mapa[x][y] == empty) {
            mapa[x][y] = boox;
        }
    }
}

void gera_mapa()
{
    for (int i =0; i<ALTURA; i++) {
        for (int j =0;j<COMPRIMENTO; j++) {
            if (j==0 ||j==COMPRIMENTO-1) {

                mapa[j][i]=wall;

            }else if (i==0||i==ALTURA-1) {

                mapa[j][i] = floor;
            }else{
                mapa[j][i]=empty;
            }   

        }

    }

}

void print_map(player player)
{   
    clear();
    for (int i=0; i<ALTURA; i++) {
        for (int j=0; j<COMPRIMENTO; j++) {  
            if (i==player.pos.y && j==player.pos.x){

                mvprintw(i,j,"%c", player_char);               
            }else {          
                mvprintw(i,j,"%c",mapa[j][i]);
            }
        }
    }
}


void move_player(player player){
    while(1){
        int direction = getch();
        switch (direction) {
            case '8':  // Cima
                if (mapa[player.pos.x][player.pos.y-1] == empty) {
                    player.pos.y--;
                }
                break;
            case '2':  // Baixo
                if (mapa[player.pos.x][player.pos.y+1] == empty) {
                    player.pos.y++;
                }
                break;
            case '4':  // Esquerda
                if (mapa[player.pos.x-1][player.pos.y] == empty) {
                    player.pos.x--;
                }
                break;
            case '6':  // Direita
                if (mapa[player.pos.x+1][player.pos.y] == empty) {
                    player.pos.x++;
                }
                break;
            case '7':  // Diagonal superior esquerda
                if (mapa[player.pos.x-1][player.pos.y-1] == empty) {
                    player.pos.x--;
                    player.pos.y--;
                }
                break;
            case '9':  // Diagonal superior direita
                if (mapa[player.pos.x+1][player.pos.y-1] == empty) {
                    player.pos.x++;
                    player.pos.y--;
                }
                break;
            case '1':  // Diagonal inferior esquerda
                if (mapa[player.pos.x-1][player.pos.y+1] == empty) {
                    player.pos.x--;
                    player.pos.y++;
                }
                break;
            case '3':  // Diagonal inferior direita
                if (mapa[player.pos.x+1][player.pos.y+1] == empty) {
                    player.pos.x++;
                    player.pos.y++;
                }
                break;
            case 'q':
                endwin();
                exit(0);
                break;
        }
        
        print_map(player);
    }
}





void libera_mapa() {
    // Libera memória alocada para o mapa
    for (int i = 0; i < max_x; i++) {
        free(mapa[i]);
    }
    free(mapa);
}





int main(){  
    player player = {player.pos.x= 80, player.pos.y= 20};
    initscr(); // Inicializa a biblioteca ncurses
    define();
    gera_mapa();
    gera_wall();
    gera_barril();

    print_map(player);
    move_player(player);

    
    getch(); // Aguarda pressionar uma tecla para sair
    
    endwin(); // Encerra o uso da biblioteca ncurses

    libera_mapa();
    
    return 0;
}