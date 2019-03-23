#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define QUEENS 8
#define ROWS 8
#define COLS 8

int solutions = 0;

bool verify(int board[ROWS][COLS]);
bool placeQueen(int board[ROWS][COLS], int row, int col);
void printBoard(int board[ROWS][COLS]);
void revertQueen(int board[ROWS][COLS], int row, int col);
bool solve_queens_problem(int placed, int board[ROWS][COLS]);

int main(int argc, char** argv) {

    int placed = 0;
    int board[8][8] = {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    solve_queens_problem(placed, board);

    return 0;
}

bool solve_queens_problem(int placed, int board[ROWS][COLS]) {
    
    if (placed == 8) {
        printBoard(board);
        return true;
    }
    else {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {

                // Place Queen
                if (!placeQueen(board, i, j)) {
                    continue;
                }
                placed++;

                // Check
                if (verify(board)) {
                    bool done = solve_queens_problem(placed, board);
                    if (done) return true;
                }

                // Revert Queen
                revertQueen(board, i, j);
                placed--;
            }
        }
    }

    return false;
}

bool verify(int board[ROWS][COLS]) {

    // check horizontal
    for (int i = 0; i < ROWS; i++) {
        
        int count = 0;
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 1) {
                count++;
            }
        }

        if (count >= 2) {
            return false;
        }
    }

    // check vertical
    for (int j = 0; j < COLS; j++) {
        
        int count = 0;
        for (int i = 0; i < ROWS; i++) {
            if (board[i][j] == 1) {
                count++;
            }
        }

        if (count >= 2) {
            return false;
        }
    }

    // check diagonal 
    for (int i = 0; i < ROWS; i++) {
        int row = i;
        int col = 0;

        int count = 0;
        while (row >= 0 && col < COLS) {
            if (board[row][col] == 1) {
                count++;
            }

            row--;
            col++;
        }

        if (count >= 2) {
            return false;
        }
    }
    for (int j = 0; j < ROWS; j++) {
        int row = 7;
        int col = j;

        int count = 0;
        while (row >= 0 && col < COLS) {
            if (board[row][col] == 1) {
                count++;
            }

            row--;
            col++;
        }

        if (count >= 2) {
            return false;
        }
    }
    for (int i = 0; i < ROWS; i++) {
        int row = i;
        int col = 7;

        int count = 0;
        while (row >= 0 && col >= 0) {
            if (board[row][col] == 1) {
                count++;
            }

            row--;
            col--;
        }

        if (count >= 2) {
            return false;
        }
    }
    for (int j = 0; j < ROWS; j++) {
        int row = 7;
        int col = j;

        int count = 0;
        while (row >= 0 && col >= 0) {
            if (board[row][col] == 1) {
                count++;
            }

            row--;
            col--;
        }

        if (count >= 2) {
            return false;
        }
    }

    return true;
}

bool placeQueen(int board[ROWS][COLS], int row, int col) {
    if (board[row][col] == 1) {
        return false;
    }
    else {
        board[row][col] = 1;
        return true;
    }
}

void printBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << board[i][j] << "   ";
        }
        cout << endl;
        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
}

void revertQueen(int board[ROWS][COLS], int row, int col) {
    board[row][col] = 0;
}

