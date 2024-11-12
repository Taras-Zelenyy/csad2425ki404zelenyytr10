#include <Arduino.h>

/// Symbol representing player X.
const char PLAYER_X = 'X';

/// Symbol representing player O.
const char PLAYER_O = 'O';

/// Constant for AI player identifier.
const String AI_PLAYER = "AI";

/// Constant for real player identifier.
const String REAL_PLAYER = "PLAYER";

/// Message indicating an invalid move.
const String INVALIDE_MSG = "INVALID";

/// Message indicating a winning state.
const String WIN_MSG = "WIN";

/// Message indicating a draw state.
const String DRAW_MSG = "DRAW";

/// Message indicating the game should continue.
const String CONTINUE_MSG = "CONTINUE";

/// Game mode for human vs human.
const int MODE_MAN_VS_MAN = 1;

/// Game mode for human vs AI.
const int MODE_MAN_VS_AI = 2;

/// Game mode for AI vs AI.
const int MODE_AI_VS_AI = 3;

/// Size of the game board.
const int BOARD_SIZE = 3;

/**
 * @brief Initializes the serial communication.
 */
void setup() {
    Serial.begin(9600);
}

/**
 * @brief Main loop to handle incoming game mode commands.
 *
 * Checks for incoming commands over serial communication and initiates
 * the appropriate game mode handler based on the received input.
 */
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

/**
 * @brief Handles the human vs human game mode.
 *
 * Validates and processes a human player’s move, updating the board and
 * checking for win or draw conditions.
 *
 * @param input The serialized input string containing game mode, player symbol, board state, and move coordinates.
 */
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

/**
 * @brief Handles the human vs AI game mode.
 *
 * Processes the human player's move, validates it, and makes the AI's move.
 * Checks for win, draw, or continuation states.
 *
 * @param input The serialized input string containing game mode, player symbol, board state, and move coordinates.
 */
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

/**
 * @brief Handles the AI vs AI game mode.
 *
 * Executes moves for both AI players, checking for game end conditions and updating
 * the board until a winner or draw is reached.
 *
 * @param input The serialized input string containing game mode, player symbol, and board state.
 */
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

/**
 * @brief Parses a serialized board state string into a 2D board array.
 *
 * Converts a board state string into a 2D array representation of the board.
 *
 * @param input The serialized board string in row-major order.
 * @param board The 2D array to populate with board state.
 */
void parseBoard(const String &input, char board[BOARD_SIZE][BOARD_SIZE]) {
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = input.charAt(index++);
        }
    }
}

/**
 * @brief Serializes the current board state into a string.
 *
 * Converts the 2D board array into a single string for communication.
 *
 * @param b The board to serialize.
 * @return String The serialized board state.
 */
String boardToString(char b[BOARD_SIZE][BOARD_SIZE]) {
    String s = "";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            s += b[i][j];
        }
    }
    return s;
}

/**
 * @brief Checks if a move is valid on the board.
 *
 * Ensures the move is within bounds and the cell is unoccupied.
 *
 * @param board The game board.
 * @param row The row index of the move.
 * @param col The column index of the move.
 * @return bool True if the move is valid, false otherwise.
 */
bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] != PLAYER_X && board[row][col] != PLAYER_O);
}

/**
 * @brief Checks if a player has won the game.
 *
 * Evaluates the board to see if the specified player has a winning configuration.
 *
 * @param board The game board.
 * @param player The player's symbol ('X' or 'O').
 * @return bool True if the player has won, false otherwise.
 */
bool checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

/**
 * @brief Checks if the board is full.
 *
 * Determines if there are any remaining empty cells on the board.
 *
 * @param board The game board.
 * @return bool True if the board is full, false otherwise.
 */
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

/**
 * @brief Gets the opponent's symbol.
 *
 * Returns the symbol of the opponent player.
 *
 * @param player The current player's symbol.
 * @return char The opponent player's symbol.
 */
char opponent(char player) {
    return (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

/**
 * @brief Implements the minimax algorithm to calculate the best move.
 *
 * Recursive minimax function to evaluate the best possible move for the AI.
 *
 * @param b The game board.
 * @param currentPlayer The current player symbol in the recursion.
 * @param aiPlayer The AI player's symbol.
 * @param depth The current depth of the recursion.
 * @return int The score of the best evaluated move.
 */
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

/**
 * @brief Determines the best move for the AI player.
 *
 * Uses minimax to evaluate and select the optimal move for the AI.
 *
 * @param b The game board.
 * @param aiPlayer The AI player's symbol.
 * @param move Array to store the row and column of the chosen move.
 */
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