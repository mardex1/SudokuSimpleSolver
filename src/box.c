#include "sudoku.h"

Box** createBoxes(){
    int x, y;
    Box ** boxes;

    boxes = (Box**)malloc(sizeof(Box*)*9);
    for(x = 0; x < 9; x++) {
        boxes[x] = (Box*)malloc(sizeof(Box));
        boxes[x]->squares = (Square**)malloc(sizeof(Square*)*9);
        boxes[x]->numbers = 0;
        boxes[x]->solvable = 9;
        
        for(y = 0; y < 9; y++) {
            boxes[x]->possible[y] = 0;
        }
    }
    return boxes;
}

void fixBoxes(int row, int col, Square *** sudoku, int num) {
    int i, j, k;
    Box* box;
    box = sudoku[row][col]->box;

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            if ((i != row || j != col) && (box->squares[i * 3 + j]->possible[num-1] == 0)) {
                box->squares[i * 3 + j]->possible[num-1] = 1;
                box->squares[i * 3 + j]->solvable--;
            }
            
        }
    }  
}

int boxSingles(Square *** sudoku, Box ** boxes) {
    int i, j, k, x, counter;
    int row, column;

    // Go through boxes
    for(k = 0; k < 9; k++) {
        // Number 1-9
        for(x = 1; x <= 9; x++) {
            counter = 0;
            // Each row in a box
            for(i = 0; i < 3; i++) {
                // Each column in a box
                for(j = 0; j < 3; j++) {
                    // printf(" %d ", boxes[k]->squares[i*3+j]->number);
                    if(boxes[k]->squares[i*3+j]->possible[x-1] == 0) {
                        row = boxes[k]->squares[i*3+j]->row;
                        column = boxes[k]->squares[i*3+j]->col;
                        counter++;
                    }
                }
                // printf("\n");
            }
            // printf("----------------\n");
            // Encontrei um número a ser posto.
            if(counter == 1) {
                sudoku[row][column]->number = x;
                for(i = 0; i < SIZE_ROWS; i++) {
                    sudoku[row][column]->possible[k] = 1;
                }
                sudoku[row][column]->solvable = 0;
                UNSOLVED--;
                fixRowCol(row, column, sudoku, sudoku[row][column]->number);
                fixBoxes(row, column, sudoku, sudoku[row][column]->number);

                return 1;
                
                
            }
        }
    }
    return 0;
}