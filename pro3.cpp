#include <stdio.h>
#include <stdbool.h>

#define PLAYER 'X'
#define AI 'O'
#define EMPTY ' '

// Function prototypes
void printBoard(char board[3][3]);
bool isMovesLeft(char board[3][3]);
int evaluate(char board[3][3]);
int minimax(char board[3][3], int depth, bool isMax);
void findBestMove(char board[3][3], int *bestMoveRow, int *bestMoveCol);
void playerMove(char board[3][3]);
void aiMove(char board[3][3]);

int main() {
    char board[3][3] = {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
    };

    printf("Tic-Tac-Toe Game: You are '%c', AI is '%c'.\n", PLAYER, AI);
    printBoard(board);

    while (true) {
        // Player's turn
        playerMove(board);
        printBoard(board);

        // Check if player won
        if (evaluate(board) == -10) {
            printf("You win!\n");
            break;
        }

        // Check for draw
        if (!isMovesLeft(board)) {
            printf("It's a draw!\n");
            break;
        }

        // AI's turn
        aiMove(board);
        printBoard(board);

        // Check if AI won
        if (evaluate(board) == 10) {
            printf("AI wins!\n");
            break;
        }

        // Check for draw
        if (!isMovesLeft(board)) {
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}

void printBoard(char board[3][3]) {
    printf("\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY)
                return true;
        }
    }
    return false;
}

int evaluate(char board[3][3]) {
    // Check rows for victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI)
                return +10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI)
                return +10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
    }

    // Check diagonals for victory
    if (board[0][0] ==
