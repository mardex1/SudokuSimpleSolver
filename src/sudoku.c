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
            printf("Failed to solve the puzzle!\n\n"); 
            break;
        }else {
            printf("Etapa %d\n\n", i);
            i++;
            printPuzzle(sudoku->squares); 
        }
    }
    if (progress == 1) {
        printf("\n\nSUDOKU WAS SOLVED SUCESSFULLY!!\n\n");
    }


    return 0;
}