#include <string>

/// Size of the game board (3x3).
const int BOARD_SIZE = 3;

/// Represents the current state of the game board.
extern char board[BOARD_SIZE][BOARD_SIZE];

/**
 * @brief Displays the current game board.
 *
 * Clears the console and prints the board, coloring cells based on player occupancy.
 */
void displayBoard();

/**
 * @brief Updates a specific cell on the board with the player's symbol.
 *
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @param player The player's symbol ('X' or 'O').
 */
void updateBoard(int row, int col, char player);

/**
 * @brief Updates the entire board using a serialized board string.
 *
 * @param boardStr A string representing the board state, where each character
 * corresponds to a cell in row-major order.
 */
void updateBoardFull(const std::string& boardStr);

/**
 * @brief Resets the board to its initial state with numbered cells.
 */
void resetBoard();

/**
 * @brief Serializes the current board state into a string.
 *
 * @return std::string A string representation of the board, with each character
 * representing a cell in row-major order.
 */
std::string serializeBoard();