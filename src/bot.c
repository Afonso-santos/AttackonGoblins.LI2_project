// #include <alloca.h>
// #include <curses.h>
// #include <math.h>
// #include <ncurses.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>


// typedef struct Position {
//     int x;
//     int y;
// } Position;



// typedef struct inventory{
//     //armas
//     int flashlight_radius;
// }inventory;


// typedef struct Player{
//     Position pos ;
//     //int health;    
//     //int attack;
//     inventory inventory;
// }player;

// typedef struct Enemy{
//     Position pos ;
//     //int health;    
//     //int attack;
//     inventory inventory;
// }Enemy;



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 10
#define COLS 10
#define OBST 1

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
    //int health;    
    //int attack;
    inventory inventory;
}player;

typedef struct Enemy{
    Position pos;
    //
}enemy;




typedef struct {
    Position parent;
    double f;
    double g;
    double h;
} node;

typedef struct {
    int row;
    int col;
} point;

double heuristic(point a, point b) {
    return sqrt(pow(a.row - b.row, 2) + pow(a.col - b.col, 2));
}

double distance(point a, point b) {
    return sqrt(pow(a.row - b.row, 2) + pow(a.col - b.col, 2));
}

void findPath(int grid[][COLS], point start, point end) {
    
    node openSet[ROWS * COLS];
    node closedSet[ROWS * COLS];
    int numOpenSet = 0;
    int numClosedSet = 0;

    openSet[numOpenSet].parent = start;
    openSet[numOpenSet].f = 0;
    openSet[numOpenSet].g = 0;
    openSet[numOpenSet].h = heuristic(start, end);
    numOpenSet++;

    while (numOpenSet > 0) {
        // Find node with lowest f value
        int currentIndex = 0;
        double lowestF = openSet[0].f;
        for (int i = 1; i < numOpenSet; i++) {
            if (openSet[i].f < lowestF) {
                currentIndex = i;
                lowestF = openSet[i].f;
            }
        }
        node current = openSet[currentIndex];
        // Check if we have reached the end
        if (current.parent.row == end.row && current.parent.col == end.col) {
            printf("Found path!\n");
            return;
        }
        // Move current node to closed set
        closedSet[numClosedSet] = current;
        numClosedSet++;
        // Remove current node from open set
        for (int i = currentIndex; i < numOpenSet - 1; i++) {
            openSet[i] = openSet[i + 1];
        }
        numOpenSet--;
        // Get neighboring nodes
        point neighbors[8];
        int numNeighbors = 0;
        for (int row = current.parent.row - 1; row <= current.parent.row + 1; row++) {
            for (int col = current.parent.col - 1; col <= current.parent.col + 1; col++) {
                if ((row >= 0 && row < ROWS) && (col >= 0 && col < COLS)) {
                    if (!(row == current.parent.row && col == current.parent.col)) {
                        if (grid[row][col] != OBST) {
                            point neighbor;
                            neighbor.row = row;
                            neighbor.col = col;
                            neighbors[numNeighbors] = neighbor;
                            numNeighbors++;
                        }
                    }
                }
            }
        }
        // Process neighboring nodes
        for (int i = 0; i < numNeighbors; i++) {
            point neighbor = neighbors[i];
            // Check if node is
                    // already in closed set
            int inClosedSet = 0;
            for (int j = 0; j < numClosedSet; j++) {
                if (closedSet[j].parent.row == neighbor.row && closedSet[j].parent.col == neighbor.col) {
                    inClosedSet = 1;
                    break;
                }
            }
            if (inClosedSet) {
                continue;
            }
            // Calculate tentative g score
            double tentativeG = current.g + distance(current.parent, neighbor);
            // Check if neighbor is in open set
            int inOpenSet = 0;
            for (int j = 0; j < numOpenSet; j++) {
                if (openSet[j].parent.row == neighbor.row && openSet[j].parent.col == neighbor.col) {
                    inOpenSet = 1;
                    break;
                }
            }
            if (!inOpenSet) {
                // Add neighbor to open set
                node neighborNode;
                neighborNode.parent = neighbor;
                neighborNode.g = tentativeG;
                neighborNode.h = heuristic(neighbor, end);
                neighborNode.f = neighborNode.g + neighborNode.h;
                openSet[numOpenSet] = neighborNode;
                numOpenSet++;
            } else {
                // Check if tentative g score is better than existing g score
                for (int j = 0; j < numOpenSet; j++) {
                    if (openSet[j].parent.row == neighbor.row && openSet[j].parent.col == neighbor.col) {
                        if (tentativeG < openSet[j].g) {
                            openSet[j].g = tentativeG;
                            openSet[j].f = openSet[j].g + openSet[j].h;
                            openSet[j].parent = current.parent;
                        }
                        break;
                    }
                }
            }
        }
    }
    printf("No path found.\n");
}



