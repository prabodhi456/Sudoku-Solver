#include <iostream>
using namespace std;

const int N = 9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}

// Function to check if a given number is safe to place in the current cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is already present in the current row or column
    for (int i = 0; i < N; i++)
        if (grid[row][i] == num || grid[i][col] == num)
            return false;

    // Check if the number is already present in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Find the first empty cell in the grid
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
            break;
    }

    // If no empty cell is found, the Sudoku puzzle is solved
    if (!isEmpty)
        return true;

    // Try placing numbers from 1 to 9 in the current empty cell
    for (int num = 1; num <= 9; num++) {
        // Check if it's safe to place the current number in the current cell
        if (isSafe(grid, row, col, num)) {
            // Place the number in the current cell
            grid[row][col] = num;

            // Recursively try to solve the Sudoku puzzle
            if (solveSudoku(grid))
                return true;

            // If placing the current number doesn't lead to a solution,
            // backtrack and try the next number
            grid[row][col] = 0;
        }
    }

    // If no number can be placed in the current cell, the puzzle cannot be solved
    return false;
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid))
        printGrid(grid);
    else
        cout << "No solution exists." << endl;

    return 0;
}
