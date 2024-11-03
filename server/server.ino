#include <Arduino.h>

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

const String AI_PLAYER = "AI";
const String REAL_PLAYER = "PLAYER";

const String INVALIDE_MSG = "INVALID";
const String WIN_MSG = "WIN";
const String DRAW_MSG = "DRAW";
const String CONTINUE_MSG = "CONTINUE";

const int MODE_MAN_VS_MAN = 1;
const int MODE_MAN_VS_AI = 2;
const int MODE_AI_VS_AI = 3;

const int BOARD_SIZE = 3;

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        int gameMode = input.substring(0).toInt();
        if (gameMode == MODE_MAN_VS_MAN) {
            handleManVsMan(input);
        } else if (gameMode == MODE_MAN_VS_AI) {
            handleManVsAI(input);
        } else if (gameMode == MODE_AI_VS_AI) {
            handleAIvsAI(input);
        }
    }
}

void handleManVsMan(String input) {
    char player = input.charAt(2);
    char board[BOARD_SIZE][BOARD_SIZE];
    parseBoard(input.substring(4, 13), board);
    int row = input.charAt(14) - '0';
    int col = input.charAt(16) - '0';

    if (isValidMove(board, row, col)) {
        board[row][col] = player;

        if (checkWin(board, player)) {
            Serial.println(WIN_MSG);
        } else if (isBoardFull(board)) {
            Serial.println(DRAW_MSG);
        } else {
            Serial.println(CONTINUE_MSG);
        }
    } else {
        Serial.println(INVALIDE_MSG);
    }
}

void handleManVsAI(String input) {
    char player = input.charAt(2);
    char board[BOARD_SIZE][BOARD_SIZE];
    parseBoard(input.substring(4, 13), board);
    int row = input.charAt(14) - '0';
    int col = input.charAt(16) - '0';
    char aiPlayer = opponent(player);

    if (isValidMove(board, row, col)) {
        board[row][col] = player;

        if (checkWin(board, player)) {
            String response = boardToString(board) + " " + WIN_MSG + "_" + REAL_PLAYER;
            Serial.println(response);
        } else if (isBoardFull(board)) {
            String response = boardToString(board) + " " + DRAW_MSG;
            Serial.println(response);
        } else {
            int aiMove[2];
            bestMove(board, aiPlayer, aiMove);
            board[aiMove[0]][aiMove[1]] = aiPlayer;

            if (checkWin(board, aiPlayer)) {
                String response = boardToString(board) + " " + WIN_MSG + "_" + AI_PLAYER;
                Serial.println(response);
            } else if (isBoardFull(board)) {
                String response = boardToString(board) + " " + DRAW_MSG;
                Serial.println(response);
            } else {
                String response = boardToString(board) + " " + CONTINUE_MSG;
                Serial.println(response);
            }
        }
    } else {
        Serial.println(INVALIDE_MSG);
    }
}

void handleAIvsAI(String input) {
    char board[BOARD_SIZE][BOARD_SIZE];
    parseBoard(input.substring(4, 13), board);
    char player = input.charAt(2);

    int aiMove[2];
    bestMove(board, player, aiMove);
    board[aiMove[0]][aiMove[1]] = player;

    if (checkWin(board, player)) {
        String response = boardToString(board) + " " + WIN_MSG + "_" + String(player);
        Serial.println(response);
    } else if (isBoardFull(board)) {
        String response = boardToString(board) + " " + DRAW_MSG;
        Serial.println(response);
    } else {
        String response = boardToString(board) + " " + CONTINUE_MSG;
        Serial.println(response);
    }
}

void parseBoard(const String &input, char board[BOARD_SIZE][BOARD_SIZE]) {
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = input.charAt(index++);
        }
    }
}

String boardToString(char b[BOARD_SIZE][BOARD_SIZE]) {
    String s = "";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            s += b[i][j];
        }
    }
    return s;
}

bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] != PLAYER_X && board[row][col] != PLAYER_O);
}

bool checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
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

int minimax(char b[BOARD_SIZE][BOARD_SIZE], char currentPlayer, char aiPlayer, int depth) {
    if (checkWin(b, aiPlayer)) {
        return 10 - depth;
    } else if (checkWin(b, opponent(aiPlayer))) {
        return depth - 10;
    } else if (isBoardFull(b)) {
        return 0;
    }

    int bestScore = (currentPlayer == aiPlayer) ? -1000 : 1000;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (b[i][j] != PLAYER_X && b[i][j] != PLAYER_O) {
                b[i][j] = currentPlayer;
                int score = minimax(b, opponent(currentPlayer), aiPlayer, depth + 1);
                b[i][j] = '1' + (i * BOARD_SIZE + j);
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

void bestMove(char b[BOARD_SIZE][BOARD_SIZE], char aiPlayer, int move[2]) {
    int bestScore = -1000;
    move[0] = -1;
    move[1] = -1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (b[i][j] != PLAYER_X && b[i][j] != PLAYER_O) {
                b[i][j] = aiPlayer;
                int score = minimax(b, opponent(aiPlayer), aiPlayer, 0);
                b[i][j] = '1' + (i * BOARD_SIZE + j);;
                if (score > bestScore) {
                    bestScore = score;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }
}