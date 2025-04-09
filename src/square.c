#include "sudoku.h"

int solveSquare(Square * square) {
    int k;
    int num;

    for(k = 0; k < SIZE_ROWS; k++) {
        if (!square->possible[k]) {
            num = k + 1;
            square->number = num;
            square->possible[k] = 1;
            square->solvable--;
            UNSOLVED--;
        }
    }
    return 1;

}