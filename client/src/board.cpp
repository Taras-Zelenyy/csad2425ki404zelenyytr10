#include <iostream>
#include <string>
#include <windows.h>

#include "../include/board.h"
#include "../include/player.h"
#include "../include/console_utils.h"

/// Initializes the game board with default numbered cells.
char board[BOARD_SIZE][BOARD_SIZE] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' } };

/**
 * @brief Resets the board to its initial state with numbered cells.
 */
void resetBoard() {
    int cell_index = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = static_cast<char>('0' + cell_index);
            cell_index++;
        }
    }
}

/**
 * @brief Displays the current state of the game board.
 *
 * Clears the console and prints the board with colored cells based on occupancy:
 * - Red for PLAYER_X
 * - Green for PLAYER_O
 * - Gray for unoccupied cells
 */
void displayBoard() {
    clearConsole();
    std::cout << "CURRENT BOARD STATE:" << std::endl;
    std::cout << "-------------\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << "| ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            char cell = board[i][j];
            if (cell == PLAYER_X) {
                setConsoleColor(DARK_RED);
            } else if (cell == PLAYER_O) {
                setConsoleColor(DARK_GREEN);
            } else {
                setConsoleColor(DARK_GRAY);
            }
            std::cout << cell;
            setConsoleColor(LIGHT_GRAY);
            std::cout << " | ";
        }
        std::cout << "\n-------------\n";
    }
}

/**
 * @brief Updates a specific cell on the board with the player's symbol.
 *
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @param player The player's symbol ('X' or 'O').
 */
void updateBoard(int row, int col, char player) {
    board[row][col] = player;
}

/**
 * @brief Updates the board with a serialized board state string.
 *
 * @param boardStr A string representing the board state in row-major order.
 * Displays an error if the string length is invalid.
 */
void updateBoardFull(const std::string& boardStr) {
    if (boardStr.length() != BOARD_SIZE * BOARD_SIZE) {
        setConsoleColor(LIGHT_RED);
        std::cerr << "[ERROR] Invalid board string length: " << boardStr.length() << std::endl;
        setConsoleColor(LIGHT_GRAY);
        return;
    }
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = boardStr[index++];
        }
    }
}

/**
 * @brief Serializes the current board state to a string.
 *
 * @return std::string A row-major representation of the board.
 */
std::string serializeBoard() {
    std::string serialized = "";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            serialized += board[i][j];
        }
    }
    return serialized;
}
