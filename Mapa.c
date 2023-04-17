#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define ALTURA 40
#define COMPRIMENTO 40
#define wall_char '#'
#define chao '.'
#define player_char '@'

typedef struct Jogador{

    int x;
    int y ;
    int health;    
    int attack;


}Player;

char mapa[ALTURA][COMPRIMENTO];


void desenha_map(char mapa[ALTURA][COMPRIMENTO],Player player )
{
    clear();

    for (int y=0; y<ALTURA; y++) {
        for (int x=0;x<COMPRIMENTO; x++) {
            if (y==player.y && x==player.x) {
                printw("%c",player_char);

            }else {
                printw("%c",mapa[y][x]);
            }
        
        }
        printw("\n");
    }   
    refresh(); 
}

void gera_mapa(int seed)
{
    srand(seed);
    for (int y=0; y<ALTURA; y++) {
        for (int x=0;x<COMPRIMENTO ; x++) {
            
            if (x==0||y==0||x==1||y==1||x==COMPRIMENTO-1 || x==COMPRIMENTO-2 || y==ALTURA-1 ||y==ALTURA-2 ) {
                mapa[y][x]=wall_char;

            }else {
                mapa[y][x] = rand() % 4 ? chao:wall_char;
                
            }
        }
    }
}



void movimento(char mapa[ALTURA][COMPRIMENTO], Player player)
{
    while (1) {

    int ch = getch();

    switch(ch) {
                case '8':
                    if (player.y > 0 && mapa[player.y-1][player.x] != wall_char) {
                        player.y--;
                    }
                    break;
                case '2':
                    if (player.y < ALTURA-1 && mapa[player.y+1][player.x] != wall_char) {
                        player.y++;
                    }
                    break;
                case '4':
                    if (player.x > 0 && mapa[player.y][player.x-1] != wall_char) {
                        player.x--;
                    }
                    break;
                case '6':
                    if (player.x < COMPRIMENTO-1 && mapa[player.y][player.x+1] != wall_char) {
                        player.x++;
                    }
                    break;
                case '1':
                    if (player.x < COMPRIMENTO-1 && mapa[player.y+1][player.x-1] != wall_char) {
                        player.x--;
                        player.y++;
                    }
                    break;
                case '3':
                    if (player.x < COMPRIMENTO-1 && mapa[player.y+1][player.x+1] != wall_char) {
                        player.x++;
                        player.y++;
                    }
                    break;
                case '7':
                    if (player.x < COMPRIMENTO-1 && mapa[player.y-1][player.x-1] != wall_char) {
                        player.x--;
                        player.y--;
                    }
                    break;
                case '9':
                    if (player.x < COMPRIMENTO-1 && mapa[player.y-1][player.x+1] != wall_char) {
                        player.x++;
                        player.y--;
                    }
                    break;
                case 'q':
                    endwin();
                    exit(0);
                    break;
                default:
                    break;
            }
            desenha_map(mapa,player);

    }
}

int main()
{
    Player player = {ALTURA/2, COMPRIMENTO/2 , 100, 15};
    int seed=time(NULL);

    gera_mapa(seed);
//---------------------------------------
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
//----------------------------------------
    desenha_map(mapa,player);
    movimento(mapa,player);



    endwin();

    return 0;
}