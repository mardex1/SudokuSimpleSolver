# SudokuSimpleSolver

A simple Sudoku solver written in C. Heavily inspired on @badcodinghabits tutorial. Great for consolidating C knowledge.


## How it works

It first uses a rule-base algorithm, basically a rule-based algorithm on a sudoku works just like a normal person would try to solve it. So it looks at the rows, columns and the boxes and try to find a square in which a number can go in. Turns out this cannot handle all sudoku puzzles. So the strategy adopted is backtracking, after the limit of the rule-based algorithm. The solver looks at a square with blank(0) and try a possible number, it keeps doing this to every blank square it sees. He may get lucky and get directly to the solution. But, in most cases, the algorithm needs to backtrack to other solution and try a different set of number in squares. Effectively, it always get to a solution. 

## Getting started

1. Clone this repository:

```
git clone https://github.com/mardex1/SudokuSimpleSolver.git
```

2. Run the code by running the makefile:

```
make
```

## In case you want to generate new python sudoku examples

1. Activate virtual enviroment for python using:

```
source venv/bin/activate
```

2. Install necessary dependencies (just one :D): 

```
pip install -r requirements.txt
```

3. Modify and Run the python file:

```
python src/generate_sudoku.py
```


Feel free to sugest changes in the code, i'm not good at C.
