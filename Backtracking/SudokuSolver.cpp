#include <iostream>
using namespace std;

bool isSafe(int val, int row, int col, int board[9][9]) {

    for (int i=0; i<9; i++) { // check for complete col
        if (board[row][i] == val) {
            return false;
        }
    }

    for (int i=0; i<9; i++) { // check for complete row
        if (board[i][col] == val) {
            return false;
        }
    }

    for (int i=0; i<9; i++) {
        if (board[3*(row/3) + i/3][3*(col/3) + i%3] == val) { // check for 3x3 matrix
            return false;
        }
    }

    return true;

}

bool isItSudoku(int board[9][9]) {
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {

            if (board[i][j] == 0) {

                for (int val = 1; val <= 9; val++) {

                    if (isSafe(val, i, j, board)) {

                        board[i][j] = val;

                        if (isItSudoku(board)) {
                            return true;
                        }
                        else {
                            board[i][j] = 0;
                        }

                    }

                }

                return false;

            }

        }
    }
    return true;
}
