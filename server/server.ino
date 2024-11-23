#include <Arduino.h>
#include "include/server_logic.h"

const String INVALID_MSG = "INVALID";

const String WIN_MSG = "WIN";

const String DRAW_MSG = "DRAW";

const String CONTINUE_MSG = "CONTINUE";

const int MODE_MAN_VS_MAN = 1;

const int MODE_MAN_VS_AI = 2;

const int MODE_AI_VS_AI = 3;

const String AI_PLAYER = "AI";

const String REAL_PLAYER = "PLAYER";

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
        Serial.println(INVALID_MSG);
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
        Serial.println(INVALID_MSG);
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
