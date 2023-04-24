#include "../includes/types/position.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define ALTURA 35             //altura do mapa
#define COMPRIMENTO 120       //comprimento do mapa
#define wall_char '#'         //o caracter de uma parede é o "#"
#define chao '.'              //o caracter para indicar que é chão é "."
#define player_char '@'       //o caracter do jogador é o "@"

typedef struct Jogador{       //define-se uma struct Jogador com sinónimo "Player" e que é constituída por:
    int x;                    //    -posição x do jogador (aumenta da esquerda para a direita)
    int y ;                   //    -posição y do jogador (aumenta de cima para baixo)
    int health;               //    -guarda a quantidade de vida
    int attack;               //    -dano da arma
}Player;

char mapa[ALTURA][COMPRIMENTO];     //define-se um mapa como sendo uma matriz

void gera_mapa(int seed)     //função para gerar o mapa 
{
    srand(seed);     //gera números aleatóios com base no valor de seed para que o "rand" escolha um desses valores
    for (int y=0; y<ALTURA; y++) {
        for (int x=0;x<COMPRIMENTO ; x++) {
            
            if (x==0||y==0||x==1||y==1||x==COMPRIMENTO-1 || x==COMPRIMENTO-2 || y==ALTURA-1 ||y==ALTURA-2 ) {
                mapa[y][x]=wall_char;        //cria as bordas do mapa com uma espessura de duas paredes

            }else {
                mapa[y][x] = rand() % 8 ? chao:wall_char;     //no resto do mapa os "#" são colocados de forma aleatória (é escolhido um número ao acaso, e caso ele seja divisível por 9 então coloca-se um chão) 
            }
        }
    }
}

void desenha_map(char mapa[ALTURA][COMPRIMENTO],Player player){      //faz-se uma função para desenhar o mapa inicial
    clear();    //para apagar o mapa que estava anteriormente desenhado no ecrã
    for (int y=0; y<ALTURA; y++) {
        for (int x=0;x<COMPRIMENTO; x++) {
            
            if (y==player.y && x==player.x) {
                printw("%c",player_char);          //assim que for atingida a posição inicial do jogador, é necessário colocar lá um "@"
            
            }else {
                printw("%c",mapa[y][x]);          //se ainda não foi atingida a posição do jogador, então o mapa é imprimido normalmente (com "#" para as paredes e "." para o chão)
            } 

        }
        printw("\n");
    }   
}

void movimento(char mapa[ALTURA][COMPRIMENTO], Player player)      //função responsável por ir alterando as coordenadas do jogador consoante as teclas pressionadas
{
    while (1) {     //para não terminar

    int ch = getch();       //guarda o caracter da tecla pressionada

    switch(ch) {    //em todos estes casos, para que o jogador se mova é necessário que este não vá contra uma parede
                case '8':      //o jogador deslocar-se-á para cima
                    if (player.y > 0 && mapa[player.y-1][player.x] != wall_char) {
                        player.y--;
                    }
                    break;
                case '2':      //o jogador deslocar-se-á para baixo
                    if (player.y < ALTURA-1 && mapa[player.y+1][player.x] != wall_char) {
                        player.y++;
                    }
                    break;
                case '4':      //o jogador deslocar-se-á para a esquerda
                    if (player.x > 0 && mapa[player.y][player.x-1] != wall_char) {
                        player.x--;
                    }
                    break;
                case '6':      //o jogador deslocar-se-á para a direita
                    if (player.x < COMPRIMENTO-1 && mapa[player.y][player.x+1] != wall_char) {
                        player.x++;
                    }
                    break;
                case '1':      //o jogador deslocar-se-á na diagonal com sentido para baixo e para a esquerda
                    if (player.x < COMPRIMENTO-1 && mapa[player.y+1][player.x-1] != wall_char) {
                        player.x--;
                        player.y++;
                    }
                    break;
                case '3':      //o jogador deslocar-se-á na diagonal com sentido para baixo e para a direita
                    if (player.x < COMPRIMENTO-1 && mapa[player.y+1][player.x+1] != wall_char) {
                        player.x++;
                        player.y++;
                    }
                    break;
                case '7':      //o jogador deslocar-se-á na diagonal com sentido para cima e para a esquerda
                    if (player.x < COMPRIMENTO-1 && mapa[player.y-1][player.x-1] != wall_char) {
                        player.x--;
                        player.y--;
                    }
                    break;
                case '9':      //o jogador deslocar-se-á na diagonal com sentido para cima e para a direita
                    if (player.x < COMPRIMENTO-1 && mapa[player.y-1][player.x+1] != wall_char) {
                        player.x++;
                        player.y--;
                    }
                    break;
                case 'q':       //encerra o jogo caso a tecla "q" seja pressionada
                    endwin();
                    exit(0);
                    break;      
            }
            desenha_map(mapa,player);    //volta-se a desenhar o mapa mas desta vez com o jogador na sua nova posição

    }
}




int main(void)
{
    Position position = create_position(0,0);
    printf("%s\n", position_to_string(position_get_left(position)).data);
}
