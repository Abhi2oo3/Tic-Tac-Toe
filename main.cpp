#include <iostream>
#include <unistd.h> // For sleep
#include <cstdlib>  // For system
using namespace std;

const int BOARD_SIZE = 3;

void clearScreen() {
    cout << "\033[H\033[2J"; // ANSI escape code to clear the screen
}

bool isValidMove(char board[][BOARD_SIZE], int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] != 'A' && board[row][col] != 'B';
}

void printBoard(char board[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j];
            if (j < BOARD_SIZE - 1) cout << " | ";
        }
        cout << endl;
        if (i < BOARD_SIZE - 1) cout << "---------" << endl;
    }
}

bool checkWin(char board[][BOARD_SIZE], char player) {
    // Check rows for a win
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }

    // Check columns for a win
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return true;
        }
    }

    // Check diagonals for a win
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}


int main() {
    char board[BOARD_SIZE][BOARD_SIZE] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' } };
    char currentPlayer = 'A';
    int move;

    char playAgain;
    do {
        int moves = 0;
        bool gameWon = false;
        clearScreen();

        while (moves < BOARD_SIZE * BOARD_SIZE) {
            printBoard(board);
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> move;

            // Convert move to row and col
            int row = (move - 1) / BOARD_SIZE;
            int col = (move - 1) % BOARD_SIZE;

            if (isValidMove(board, row, col)) {
                board[row][col] = currentPlayer;
                moves++;

                if (checkWin(board, currentPlayer)) {
                    gameWon = true;
                    break;
                }

                currentPlayer = (currentPlayer == 'A') ? 'B' : 'A';
            }
            else {
                cout << "Invalid move. Try again." << endl;
                sleep(1); // Sleep for 1 second on Linux
            }

            clearScreen();
        }

        printBoard(board);

        if (gameWon) {
            cout << "Player " << currentPlayer << " wins!" << endl;
        }
        else {
            cout << "It's a draw!" << endl;
        }

        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;
        if (playAgain == 'Y' || playAgain == 'y') {
            currentPlayer = 'A';
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    board[i][j] = '1' + i * BOARD_SIZE + j;
                }
            }
        }
    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "Goodbye!" << endl;
    return 0;
}
