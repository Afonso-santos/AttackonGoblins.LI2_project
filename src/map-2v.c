#include <curses.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALTURA  49
#define COMPRIMENTO 180


#define wall '#'
#define floor '#'
#define boox '='
#define empty ' '
#define player_char '@' 
#define parede '.'

char mapa[COMPRIMENTO][ALTURA];
int tamanho = 5;

#define Shapes 3

typedef enum { TRIANGLE, SQUARE, CIRCLE } Shape;
typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Jogador{
    int x;
    int y ;
    //int health;    
    //int attack;
}Player;


void gera_Triangle(int tamanho, Position pos)
{
    int i, j;
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho - i; j++) {

            if (mapa[pos.x+j][pos.y+i]!=wall && mapa[pos.x+j][pos.y+i]!=floor) {

                mapa[pos.x + j][pos.y + i] = parede;
            }
            
        }
       
    }
}


void gera_Square(int tamanho,Position pos)
{   
    for (int i=0; i<tamanho; i++) {
        for (int j=0;j<tamanho ; j++) {
            
            if (mapa[pos.x+j][pos.y+i]!=wall && mapa[pos.x+j][pos.y+i]!=floor) {
                
                mapa[pos.x + j][pos.y + i] = parede;
            }
       }
    }

}



void gera_Circle(int tamanho, Position pos)
{
    int x = 0;
    int y = tamanho;
    int d = 3 - 2 * tamanho;
    int densidade = 6; // Ajuste o valor de densidade para aumentar ou diminuir a densidade do círculo

    while (x <= y) {
        for (int i = 0; i < densidade; i++) {
            if (mapa[pos.x + x][pos.y + y - i] != wall &&mapa[pos.x + x][pos.y + y - i] != floor) {
                mapa[pos.x + x][pos.y + y - i] = parede;
            }
            if (mapa[pos.x - x][pos.y + y - i] != wall && mapa[pos.x + x][pos.y + y - i] != floor) {
                mapa[pos.x - x][pos.y + y - i] = parede;
            }
            if (mapa[pos.x + x][pos.y - y + i] != wall && mapa[pos.x + x][pos.y + y - i] != floor) {
                mapa[pos.x + x][pos.y - y + i] = parede;
            }
            if (mapa[pos.x - x][pos.y - y + i] != wall && mapa[pos.x + x][pos.y + y - i] != floor) {
                mapa[pos.x - x][pos.y - y + i] = parede;
            }
            if (mapa[pos.x + y - i][pos.y + x] != wall && mapa[pos.x + x][pos.y + y - i] != floor) {
                mapa[pos.x + y - i][pos.y + x] = parede;
            }
            if (mapa[pos.x - y + i][pos.y + x] != wall && mapa[pos.x + x][pos.y + y - i] != floor) {
                mapa[pos.x - y + i][pos.y + x] = parede;
            }
            if (mapa[pos.x + y - i][pos.y - x] != wall && mapa[pos.x + x][pos.y + y - i] != floor) {
                mapa[pos.x + y - i][pos.y - x] = parede;
            }
            if (mapa[pos.x - y + i][pos.y - x] != wall && mapa[pos.x + x][pos.y + y - i] != floor) {
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

    int num_paredes = rand() % 6 + 35; 

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
    int num_barris = rand() % 11 +35; 

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
            if (j==0 ||j==COMPRIMENTO-1 ) {

                mapa[j][i]=wall;

            }else if (i==0||i==ALTURA-1) {

                mapa[j][i] = floor;
            }else{
                mapa[j][i]=empty;
            }   

        }

    }

}

void print_map(char mapa[COMPRIMENTO][ALTURA], Player player)
{   
    clear();
    for (int i=0; i<ALTURA; i++) {
        for (int j=0; j<COMPRIMENTO; j++) {  
            if (i==player.y && j==player.x){
                printw("%c", player_char);
            }else {          
                mvprintw(i,j,"%c",mapa[j][i]);
            }
        }
    }
}

void move_player(char mapa[COMPRIMENTO][ALTURA], Player player){
    while(1){
        int direction = getch();
        switch (direction) {
            case '8':  // Cima
                if (mapa[player.x][player.y-1] == empty) {
                    player.y--;
                }
                break;
            case '2':  // Baixo
                if (mapa[player.x][player.y+1] == empty) {
                    player.y++;
                }
                break;
            case '4':  // Esquerda
                if (mapa[player.x-1][player.y] == empty) {
                    player.x--;
                }
                break;
            case '6':  // Direita
                if (mapa[player.x+1][player.y] == empty) {
                    player.x++;
                }
                break;
            case '7':  // Diagonal superior esquerda
                if (mapa[player.x-1][player.y-1] == empty) {
                    player.x--;
                    player.y--;
                }
                break;
            case '9':  // Diagonal superior direita
                if (mapa[player.x+1][player.y-1] == empty) {
                    player.x++;
                    player.y--;
                }
                break;
            case '1':  // Diagonal inferior esquerda
                if (mapa[player.x-1][player.y+1] == empty) {
                    player.x--;
                    player.y++;
                }
                break;
            case '3':  // Diagonal inferior direita
                if (mapa[player.x+1][player.y+1] == empty) {
                    player.x++;
                    player.y++;
                }
                break;
            case 'q':
                endwin();
                exit(0);
                break;
        }
        print_map(mapa, player);
    }
}


int main()
{   
    Player player = {COMPRIMENTO/2, ALTURA/2};
    initscr(); // Inicializa a biblioteca ncurses
    
    gera_mapa();
    gera_wall();
    gera_barril();

    print_map(mapa, player);
    move_player(mapa, player);
    
    getch(); // Aguarda pressionar uma tecla para sair
    
    endwin(); // Encerra o uso da biblioteca ncurses
    
    return 0;
}