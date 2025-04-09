#include "sudoku.h"

Sudoku * createSudoku(Square*** squares, Box ** boxes) {
    Sudoku * sudoku;
    sudoku = (Sudoku*)malloc(sizeof(Sudoku));

    sudoku->squares = squares;
    sudoku->boxes = boxes;

    return sudoku;
}

int checkColumns(Square*** sudoku) {
    int i, j, k, cont;
    int row, col;
    for(j = 0; j < SIZE_COLUMNS; j++) {
        for (k = 1; k <= 9; k++) {
            cont = 0;
            for(i = 0; i < SIZE_COLUMNS; i++) {
                if(sudoku[i][j]->possible[k-1] == 0) {
                    cont++;
                    row = i;
                    col = j;
                }
                if(cont == 2) {
                    break;
                }
            }
            if (cont == 1) {
                sudoku[row][col]->number = k;
                for(j = 0; j < SIZE_ROWS; j++) {
                    sudoku[row][col]->possible[j] = 1;
                }
                sudoku[row][col]->solvable = 0;
                UNSOLVED--;
                fixRowCol(row, col, sudoku, sudoku[row][col]->number);
                fixBoxes(row, col, sudoku, sudoku[row][col]->number);
    
                return 1;
            }
        }
    }
    return 0;
}

int checkRows(Square*** sudoku) {
    int i, j, k, cont;
    int row, col;
    for(i = 0; i < SIZE_ROWS; i++) {
        for (k = 1; k <= 9; k++) {
            cont = 0;
            for(j = 0; j < SIZE_COLUMNS; j++) {
                if(sudoku[i][j]->possible[k-1] == 0) {
                    cont++;
                    row = i;
                    col = j;
                }
                if(cont == 2) {
                    break;
                }
            }
            if (cont == 1) {
                sudoku[row][col]->number = k;
                for(j = 0; j < SIZE_ROWS; j++) {
                    sudoku[row][col]->possible[j] = 1;
                }
                sudoku[row][col]->solvable = 0;
                UNSOLVED--;
                fixRowCol(row, col, sudoku, sudoku[row][col]->number);
                fixBoxes(row, col, sudoku, sudoku[row][col]->number);
    
                return 1;
            }
        }
    }
    return 0;
}


void fixRowCol(int row, int col, Square *** sudoku, int num) {
    int i, j, k;
    for(k = 0; k < SIZE_ROWS; k++) {
        sudoku[row][col]->possible[k] = 1;
    }   
    
    for(i = 0; i < SIZE_ROWS; i++) {
        if (i != row && (sudoku[i][col]->possible[num-1] == 0)) {
                sudoku[i][col]->possible[num-1] = 1;
                sudoku[i][col]->solvable--;
        }
    }

    for(j = 0; j < SIZE_COLUMNS; j++) {
        if (j != col && (sudoku[row][j]->possible[num-1] == 0)) {
                sudoku[row][j]->possible[num-1] = 1; 
                sudoku[row][j]->solvable--;
        }
    }
    
}

Sudoku * setUpPuzzle(int ** puzzle) {
    Square *** sudoku;
    Box ** boxes;
    int i, j, k;
    int currentBox = 0;

    sudoku = (Square***)malloc(sizeof(Square**)*9);
    boxes = createBoxes(); 

    for (i = 0; i < SIZE_ROWS; i++) {
        sudoku[i] = (Square**)malloc(sizeof(Square*)*9);
        
        for(j = 0; j < SIZE_COLUMNS; j++) {
            sudoku[i][j] = (Square*)malloc(sizeof(Square)*9);

            sudoku[i][j]->number = puzzle[i][j];
            
            for(k = 0; k < SIZE_ROWS; k++) {
                sudoku[i][j]->possible[i] = 0;
            }            
            sudoku[i][j]->solvable = 9;
            sudoku[i][j]->row = i;
            sudoku[i][j]->col = j;
            
            boxes[currentBox]->squares[boxes[currentBox]->numbers] = sudoku[i][j];
            sudoku[i][j]->box = boxes[currentBox];
            boxes[currentBox]->numbers++;

            if (j == 2 || j == 5) currentBox++;
        }
        
        if(i == 2)
            currentBox = 3; 
        else if(i == 5)
            currentBox = 6; 
        else
            currentBox -= 2;
    }
    
    for (i = 0; i < SIZE_ROWS; i++) {
        
        for(j = 0; j < SIZE_COLUMNS; j++) {
            if (sudoku[i][j]->number) {
                sudoku[i][j]->solvable = 0;
                fixRowCol(i, j, sudoku, sudoku[i][j]->number);
                fixBoxes(i, j, sudoku, sudoku[i][j]->number);
                UNSOLVED--;
            }
        }
    }

    // for(k = 0; k < SIZE_ROWS; k++) {
    //     printf("%d %d %d\n", sudoku[0][3]->solvable, sudoku[0][3]->possible[k], k+1);
    // }
    // printf("%d\n", UNSOLVED);

    return createSudoku(sudoku, boxes);
}

int checkPuzzle(Square *** sudoku, Box ** boxes){
    int i, j;
    // for (i = 0; i < SIZE_ROWS; i++) {
    //     for(j = 0; j < SIZE_COLUMNS; j++) {
    //         printf("%d | ", sudoku[i][j]->solvable);
    //     }printf("\n");
    // }
    // printf("---------------------------------------------\n");
    for (i = 0; i < SIZE_ROWS; i++) {
        for(j = 0; j < SIZE_COLUMNS; j++) {
            // printf("%d | ", sudoku[i][j]->solvable);
            if(sudoku[i][j]->solvable == 1) {
                solveSquare(sudoku[i][j]);
                fixRowCol(i, j, sudoku, sudoku[i][j]->number);
                fixBoxes(i, j, sudoku, sudoku[i][j]->number);

                return 1;
            }
        }
    }

    if (checkRows(sudoku)) return 1;
    else if(checkColumns(sudoku)) return 1;
    // for (i = 0; i < SIZE_ROWS; i++) {
    //     for(j = 0; j < SIZE_COLUMNS; j++) {
    //         printf("%d | ", sudoku[i][j]->solvable);
    //     }printf("\n");
    // }
    // printf("---------------------------------------------\n");
    return boxSingles(sudoku, boxes);
}

// Creating the puzzle and showing it to the user
int ** createPuzzle(){
    int ** puzzle;
    int i, j;
    int array[9][9];
    FILE * fh;
    fh = fopen("sudoku_puzzles.txt", "r");
    char * line = NULL;
    char ** sudoku_puzzles = (char**)malloc(sizeof(char*)*100);
    i = 0;
    if (fh != NULL) {
        size_t line_buffer_len = 0;
        while(getline(&line, &line_buffer_len, fh) != -1) {
            sudoku_puzzles[i] = strdup(line);
            i++;
        }
    } else printf("Error opening file.\n");
    printf("\n------------------------------------------------\n\n\n\n");   
    srand(time(NULL));
    int r = rand();
    r = r % 100;
    printf("%d\n", r);

    char * puzzle_line = sudoku_puzzles[r];
    char * token = strtok(puzzle_line, " ");
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            array[i][j] = atoi(token);
            token = strtok(NULL, " ");
        }
    }

    puzzle = (int**)malloc(sizeof(int*)*9);
    for (i = 0; i < SIZE_ROWS; i++) {
        puzzle[i] = (int*)malloc(sizeof(int)*9);
        
        for(j = 0; j < SIZE_COLUMNS; j++) {
            puzzle[i][j] = array[i][j];
        }
    }
    return puzzle;
}

void printPuzzle(Square *** puzzle) {
    int i, j;

    for(i = 0; i < 9; i++) {
        if ((i) % 3 == 0 ) printf(" -------------------------------------\n");
        for(j = 0; j < 9; j++) {
            if((j) % 3 == 0 ) printf(" | ");
            printf(" %d ", puzzle[i][j]->number); // %d -> integer
            
        }printf(" | \n");
    }printf(" -------------------------------------\n");
}