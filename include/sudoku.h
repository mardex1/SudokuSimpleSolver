#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

extern int UNSOLVED; // Keeps track of how many squares have been solved.  
extern int SIZE_ROWS;
extern int SIZE_COLUMNS;

typedef struct Sudoku{
    struct Square *** squares;
    struct Box ** boxes;
}Sudoku;

typedef struct Box{
    struct Square ** squares;
    int numbers;
    int possible[9];
    int solvable;
    struct Box * next;
}Box;

typedef struct Square{
    int number;
    /*[1][1][1][1][1][1][1][1][1]
       1  2  3  4  5  6  7  8  9
    Cada bit diz se nessa posição esse número é presente.*/
    int possible[9];
    int solvable;
    Box* box;
    int row;
    int col;
}Square;

int ** createPuzzle();
void printPuzzle(Square *** puzzle);
Sudoku * setUpPuzzle(int ** puzzle);

Sudoku * createSudoku(Square *** squares, Box ** boxes);

int checkPuzzle(Square *** sudoku, Box ** boxes);
int solveSquare(Square * square);
void fixRowCol(int row, int col, Square *** sudoku, int num);
int checkRows(Square*** squares);
int checkColumns(Square*** squares);

//Box functions
Box** createBoxes();
void fixBoxes(int row, int col, Square *** sudoku, int num); 
int boxSingles(Square *** sudoku, Box ** boxes);

#endif