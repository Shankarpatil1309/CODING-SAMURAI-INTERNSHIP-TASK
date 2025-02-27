#include <iostream>
#include <limits>

using namespace std;

#define PLAYER 'X'
#define AI 'O'
#define EMPTY ' '

// Function prototypes
void printBoard(char board[3][3]);
bool isMovesLeft(char board[3][3]);
int evaluate(char board[3][3]);
int minimax(char board[3][3], int depth, bool isMax);
void findBestMove(char board[3][3], int &bestMoveRow, int &bestMoveCol);
void playerMove(char board[3][3]);
void aiMove(char board[3][3]);

int main() {
    char board[3][3] = {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
    };

    cout << "Tic-Tac-Toe Game: You are '" << PLAYER << "', AI is '" << AI << "'." << endl;
    printBoard(board);

    while (true) {
        // Player's turn
        playerMove(board);
        printBoard(board);

        // Check if player won
        if (evaluate(board) == -10) {
            cout << "You win!" << endl;
            break;
        }

        // Check for draw
        if (!isMovesLeft(board)) {
            cout << "It's a draw!" << endl;
            break;
        }

        // AI's turn
        aiMove(board);
        printBoard(board);

        // Check if AI won
        if (evaluate(board) == 10) {
            cout << "AI wins!" << endl;
            break;
        }

        // Check for draw
        if (!isMovesLeft(board)) {
            cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}

void printBoard(char board[3][3]) {
    cout << "\n";
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            cout << board[row][col] << " ";
            if (col < 2) cout << "| ";
        }
        cout << endl;
        if (row < 2) cout << "---------" << endl;
    }
    cout << "\n";
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
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != EMPTY) {
            return (board[row][0] == AI) ? 10 : -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != EMPTY) {
            return (board[0][col] == AI) ? 10 : -10;
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY) {
        return (board[0][0] == AI) ? 10 : -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY) {
        return (board[0][2] == AI) ? 10 : -10;
    }

    return 0; // No winner yet
}

int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10) return score - depth;  // Favor quick AI wins
    if (score == -10) return score + depth; // Favor delaying loss
    if (!isMovesLeft(board)) return 0; // Draw

    if (isMax) { // AI's turn (maximize)
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else { // Player's turn (minimize)
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

void findBestMove(char board[3][3], int &bestMoveRow, int &bestMoveCol) {
    int bestVal = numeric_limits<int>::min();
    bestMoveRow = -1;
    bestMoveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMoveRow = i;
                    bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

void playerMove(char board[3][3]) {
    int row, col;
    do {
        cout << "Enter your move (row and column: 0-2): ";
        cin >> row >> col;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            row = col = -1;
        }
    } while (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMPTY);

    board[row][col] = PLAYER;
}

void aiMove(char board[3][3]) {
    int bestMoveRow, bestMoveCol;
    findBestMove(board, bestMoveRow, bestMoveCol);
    board[bestMoveRow][bestMoveCol] = AI;
    cout << "AI played at " << bestMoveRow << " " << bestMoveCol << endl;
}
