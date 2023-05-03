#include <alloca.h>
#include <curses.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int max_x, max_y;
char **map;

void define() {
    // Inicializa a biblioteca ncurses
    initscr();

    // Obtém as dimensões da tela
    max_y = getmaxy(stdscr);
    max_x = getmaxx(stdscr);

    map = malloc(sizeof(char*) * max_x);
    for (int i = 0; i < max_x; i++) {
        map[i] = malloc(sizeof(char) * max_y);
    }
}



#define HEIGHT (max_y-7)
#define LENGTH (max_x-58)
    
#define player_char '@'
#define edge '#'

#define boox '='
#define empty '.'
#define obstacle '+'
#define flashlight '!'


// char map[LENGTH][HEIGHT];
int SIZE = 5;

#define Shapes 3

typedef enum { TRIANGLE, SQUARE, CIRCLE } Shape;
typedef struct Position {
    int x;
    int y;
} Position;

typedef struct inventory{
    //armas
    int flashlight_radius;
}inventory;

typedef struct Player{
    Position pos ;
    inventory inventory;
    //int health;    
    //int attack;
}player;









int check(int x, int y) {
    if (x < 2 || x >= LENGTH - 2|| y < 2 || y >= HEIGHT - 2) {
        return 0;
    }
    if (map[x][y] != edge ) {
        return 1;
    } else {
        return 0;
    }
}


int check_player(int x, int y) {
    if (x <= 2 || x >= LENGTH - 2|| y <= 2 || y >= HEIGHT - 2) {
        return 0;
    }
    if (map[x][y] == empty && x>2 && x<LENGTH-2 && y>2 && y<HEIGHT-2) {
        
        return 1;
    } else {
        return 0;
    }
}




void create_Triangle(int SIZE, Position pos)
{
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE - i; j++) {

            if (check(pos.x+j,pos.y+i)) {

                map[pos.x + j][pos.y + i] = obstacle;
            }
            
        }
       
    }
}


void create_Square(int SIZE,Position pos)
{   
    for (int i=0; i<SIZE; i++) {
        for (int j=0;j<SIZE ; j++) {
            
            if (check(pos.x+j,pos.y+i)) {
                
                map[pos.x + j][pos.y + i] = obstacle;
            }
       }
    }

}



void create_Circle(int SIZE, Position pos)
{
    int x = 0;
    int y = SIZE;
    int d = 3 - 2 * SIZE;
    int density = SIZE+1; // Ajuste o valor de density para aumentar ou diminuir a density do círculo

    while (x <= y) {
        for (int i = 0; i < density; i++) {
            if (check(pos.x+x,pos.y+y-i)) {
                map[pos.x + x][pos.y + y - i] = obstacle;
            }
            if (check(pos.x-x,pos.y+y-i)) {
                map[pos.x - x][pos.y + y - i] = obstacle;
            }
            if (check(pos.x+x,pos.y-y+i)) {
                map[pos.x + x][pos.y - y + i] = obstacle;
            }
            if (check(pos.x-x,pos.y-y+i)) {
                map[pos.x - x][pos.y - y + i] = obstacle;
            }
            if (check(pos.x+y-i,pos.y+x)) {
                map[pos.x + y - i][pos.y + x] = obstacle;
            }
            if (check(pos.x-y+i,pos.y+x)) {
                map[pos.x - y + i][pos.y + x] = obstacle;
            }
            if (check(pos.x+y-i,pos.y-x)) {
                map[pos.x + y - i][pos.y - x] = obstacle;
            }
            if (check(pos.x-y+i,pos.y-x)) {
                map[pos.x - y + i][pos.y - x] = obstacle;
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

void create_edge()
{
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
                create_Triangle(SIZE, pos);
                break;
            case SQUARE:
                create_Square(SIZE, pos);
                break;
            case CIRCLE:
                create_Circle(SIZE, pos);
                break;
            default:
                break;
        }
    }
}


void create_barrel()
{
    srand(time(0));
    int num_barris = rand() % 16 +35; 

    for (int i = 0; i < num_barris; i++) {
        int x = rand() % (LENGTH - 2) ; 
        int y = rand() % (HEIGHT - 2) ;

        if (map[x][y] == empty) {
            map[x][y] = boox;
        }
    }
}

void create_flashlight(){
    srand(time(0));
    int x = rand() % (LENGTH - 2) ; 
    int y = rand() % (HEIGHT - 2) ;
    if (map[x][y] == empty) {
        map[x][y] = flashlight;
    }
}

void remove_flashlight(){
    for (int y=0; y<HEIGHT; y++){
        for (int x=0; x<LENGTH; x++){
            if (map[x][y] == flashlight) {
                map[x][y] = empty;
            }
        }
    }
}

void create_map()
{
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


void print_map(player player)
{   
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



void free_map() {
    // Libera memória alocada para o map
    for (int i = 0; i < max_x; i++) {
        free(map[i]);
    }
    free(map);
}

// ----------------------------------------------" movimento" ----------------------------------------

void move_player(player player){
    while(1){
        int direction = getch();
        switch (direction) {
            case 'w':  // Cima
                if (map[player.pos.x][player.pos.y-1] == empty ) {
                    player.pos.y--;
                }
                break;
            case 's':  // Baixo
                if (map[player.pos.x][player.pos.y+1] == empty) {
                    player.pos.y++;
                }
                break;
            case 'a':  // Esquerda
                if (map[player.pos.x-1][player.pos.y] == empty) {
                    player.pos.x--;
                }
                break;
            case 'd':  // Direita
                if (map[player.pos.x+1][player.pos.y] == empty) {
                    player.pos.x++;
                }
                break;
            case '7':  // Diagonal superior esquerda
                if (map[player.pos.x-1][player.pos.y-1] == empty) {
                    player.pos.x--;
                    player.pos.y--;
                }
                break;
            case '9':  // Diagonal superior direita
                if (map[player.pos.x+1][player.pos.y-1] == empty) {
                    player.pos.x++;
                    player.pos.y--;
                }
                break;
            case '1':  // Diagonal inferior esquerda
                if (map[player.pos.x-1][player.pos.y+1] == empty) {
                    player.pos.x--;
                    player.pos.y++;
                }
                break;
            case '3':  // Diagonal inferior direita
                if (map[player.pos.x+1][player.pos.y+1] == empty) {
                    player.pos.x++;
                    player.pos.y++;
                }
                break;
            case 'f':  // apanhar lanterna
                if (map[player.pos.x][player.pos.y-1]==flashlight || map[player.pos.x][player.pos.y+1]==flashlight || map[player.pos.x-1][player.pos.y]==flashlight || map[player.pos.x+1][player.pos.y]==flashlight || map[player.pos.x-1][player.pos.y-1]==flashlight || map[player.pos.x+1][player.pos.y-1]==flashlight || map[player.pos.x-1][player.pos.y+1]==flashlight || map[player.pos.x+1][player.pos.y+1]==flashlight) {
                    remove_flashlight();
                    player.inventory.flashlight_radius=9;
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


player create_coordinates() {
    player new_player;
    srand(time(NULL));
    while (check_player(new_player.pos.x, new_player.pos.y) != 1){
        new_player.pos.x = (rand() % (LENGTH - 2));
        new_player.pos.y = (rand() % (HEIGHT - 2));
    }
    return new_player;
}

//------------------------------------------- " movimento"---------------------------------------



int main() {
    initscr(); // Inicializa a biblioteca ncurses
    curs_set(0);
    define();
    
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

    create_map();
    create_edge();
    create_barrel();
    create_flashlight();

    player new_player = create_coordinates();
    new_player.inventory.flashlight_radius=6; // cria uma nova estrutura player com coordenadas aleatórias
    print_map(new_player);
    move_player(new_player);

    getch(); // Aguarda pressionar uma tecla para sair

    endwin(); // Encerra o uso da biblioteca ncurses

    free_map();

    return 0;
}