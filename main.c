/*
GAME OF LIFE

- grid 
- cell
- rules
  - Any live cell with fewer than two live neighbors dies, as if by underpopulation.
  - Any live cell with two or three live neighbors lives on to the next generation.
  - Any live cell with more than three live neighbors dies, as if by overpopulation.
  - Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
  for live
  if n <= 2 && n >= 3 dies
  else lives

...
- redering
- corner position checking (if xNeighbourPosition > width don't check)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randnum(int min, int max) {
    return (((rand() % (int)(((max) + 1) - min))) + min);
}

typedef struct Cell {
    int x;
    int y;
    int curState;
    int nextState;
} Cell;

void initRandCells(size_t x, Cell grid[x][x]) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            Cell *cell = &grid[i][j];
            cell->curState = (randnum(1, 8999) % 2);
            if (cell->curState != 0 && cell->curState != 1) {
                fprintf(stderr, "Non-binary value %d tryied to be assigned to cell %d %d\n", cell->curState, i, j);
            }
            cell->x = j;
            cell->y = i;
        }
    }
    return;
}

void setNextState(size_t x, Cell grid[x][x]) {
    int aliveNeighbors;
    Cell *cell;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            cell = &grid[i][j];
            aliveNeighbors = 0;
            for (int ci = i - 1; ci <= i + 1; ci++) {
                for (int cj = j - 1; cj <= j + 1; cj++) {
                    // is current cell
                    if (ci == i && cj == j) {
                        continue;
                    }
                    // check out of bounds
                    else if (ci <= 0 || cj <= 0 || ci >= x || cj >= x) {
                        continue;
                    }
                    // is neighbors dead
                    else if (grid[ci][cj].curState == 0) {
                        continue;
                    } else {
                         aliveNeighbors++;
                    }
                }
            }
            /*
              - Any live cell with fewer than two live neighbors dies, as if by underpopulation.
              - Any live cell with two or three live neighbors lives on to the next generation.
              - Any live cell with more than three live neighbors dies, as if by overpopulation.
              - Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
            */
            if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                cell->nextState = 0;
            } else if (cell->curState == 1 && (aliveNeighbors == 2 || aliveNeighbors == 3)){
                cell->nextState = 1;
            } else if (cell->curState == 0 && aliveNeighbors == 3) {
                cell->nextState = 1;
            }
        }
    }
    return;
}
// when printing works, still 0s
void setCurState(size_t x, Cell grid[x][x]) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            Cell *cell = &grid[i][j];
            cell->curState = cell->nextState;
        }
    }
    return;
}

//works on first round, second all 0s
void renderRound(size_t x, Cell grid[x][x]) {
    printf("\n");
    printf("\n");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            Cell *cell = &grid[i][j];
            if (cell->curState == 1) {
                printf("@");
            } else {
                printf("_");
            }
            if (j < x - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
    return;
}

int main() {
    srand(time(NULL));
    const int gridSize = 16;
    Cell grid [gridSize][gridSize];
    int round = 0;

    while (1) {
        printf("round %d\n", round);
        if (round == 0) {
            printf("Initializing cells randomly\n");
            initRandCells(gridSize, grid);
        }

        printf("Setting Next State\n");
        setNextState(gridSize, grid);
        printf("rendering\n");
        renderRound(gridSize, grid);
        round++;

        printf("Go to next round? [0/1]\n");
        int playAgain;
        scanf("%d", &playAgain);
        if (playAgain != 1) {
            printf("%c", playAgain);
            break;
        } else {
            setCurState(gridSize, grid);
            continue;
        }
    }
    return 0;
}
