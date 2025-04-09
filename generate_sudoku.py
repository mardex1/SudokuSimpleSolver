from sudoku import Sudoku
import random

with open("sudoku_puzzles.txt", "w") as f:
    for _ in range(100):
        puzzle = Sudoku(3, seed=random.randint(1, 1000)).difficulty(0.5)
        flat = [cell if cell is not None else 0 for row in puzzle.board for cell in row]
        f.write(" ".join(map(str, flat)) + "\n")