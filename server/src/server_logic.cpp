#include "../include/server_logic.h"

#ifdef TEST_ENVIRONMENT
void parseBoard(const std::string &input, char board[BOARD_SIZE][BOARD_SIZE]) {
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = input[index++];
        }
    }
}

std::string boardToString(char board[BOARD_SIZE][BOARD_SIZE]) {
    std::string s = "";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            s += board[i][j];
        }
    }
    return s;
}
#else
void parseBoard(const String &input, char board[BOARD_SIZE][BOARD_SIZE]) {
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = input.charAt(index++);
        }
    }
}

String boardToString(char board[BOARD_SIZE][BOARD_SIZE]) {
    String s = "";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            s += board[i][j];
        }
    }
    return s;
}
#endif


bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE &&
            board[row][col] != PLAYER_X && board[row][col] != PLAYER_O);
}

bool checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool isBoardFull(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != PLAYER_X && board[i][j] != PLAYER_O) {
                return false;
            }
        }
    }
    return true;
}

char opponent(char player) {
    return (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

int minimax(char board[BOARD_SIZE][BOARD_SIZE], char currentPlayer, char aiPlayer, int depth) {
    if (checkWin(board, aiPlayer)) {
        return 10 - depth;
    } else if (checkWin(board, opponent(aiPlayer))) {
        return depth - 10;
    } else if (isBoardFull(board)) {
        return 0;
    }

    int bestScore = (currentPlayer == aiPlayer) ? -1000 : 1000;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != PLAYER_X && board[i][j] != PLAYER_O) {
                char temp = board[i][j];
                board[i][j] = currentPlayer;
                int score = minimax(board, opponent(currentPlayer), aiPlayer, depth + 1);
                board[i][j] = temp;
                if (currentPlayer == aiPlayer) {
                    if (score > bestScore)
                        bestScore = score;
                } else {
                    if (score < bestScore)
                        bestScore = score;
                }
            }
        }
    }
    return bestScore;
}

void bestMove(char board[BOARD_SIZE][BOARD_SIZE], char aiPlayer, int move[2]) {
    int bestScore = -1000;
    move[0] = -1;
    move[1] = -1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != PLAYER_X && board[i][j] != PLAYER_O) {
                char temp = board[i][j];
                board[i][j] = aiPlayer;
                int score = minimax(board, opponent(aiPlayer), aiPlayer, 0);
                board[i][j] = temp;
                if (score > bestScore) {
                    bestScore = score;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }
}