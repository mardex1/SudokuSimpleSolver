from sudoku import Sudoku
import random

difficulty = float(input("Give me a difficulty from 0.0 to 1.0:\n"))

with open("sudoku_puzzles.txt", "w") as f:
    for _ in range(100):
        puzzle = Sudoku(seed=random.randint(1, 1000)).difficulty(difficulty)
        flat = [cell if cell is not None else 0 for row in puzzle.board for cell in row]
        f.write(" ".join(map(str, flat)) + "\n")

print(f"Sudokus were generated!\nDifficulty={difficulty}\n")