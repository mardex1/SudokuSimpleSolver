#include "sudoku.h"

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main() {
    int ** puzzle;
    int progress;
    Sudoku * sudoku;
    puzzle = createPuzzle();

    sudoku = setUpPuzzle(puzzle); // Pega a matriz de inteiros e retorna um array triplo de squares

    printPuzzle(sudoku->squares); 

    int i = 1;
    while(UNSOLVED > 0){
        progress = checkPuzzle(sudoku->squares, sudoku->boxes); // Checa se existe algum square com solvable=1.  
        if (progress == 0) {
            break;
        }else {
            printf("Etapa %d\n\n", i);
            i++;
            printPuzzle(sudoku->squares); 
        }
    }
    if (progress == 1) {
        printf("\n\nSUDOKU WAS SOLVED SUCESSFULLY!!\n\n");
    }else {
        printf("\n\nSUDOKU WAS NOT SOLVED USING RULE-BASED ALGORITHM, NEED TO USE BACKTRACKING ALGORITHM\n\n");
        printf("BEFORE BACKTRACKING\n");
        printPuzzle(sudoku->squares);

        if(backtracking(sudoku->squares, sudoku->boxes)) {
            printf("AFTER BACKTRACKING\n");
            printPuzzle(sudoku->squares);
        }else{
            printf("\n\nOCORREU UM ERRO NO BACKTRACKING\n\n");
        }
    }

    freeSudoku(sudoku, puzzle);
    
    return 0;
}