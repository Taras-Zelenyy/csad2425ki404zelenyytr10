#include "../include/format_message.h"
#include <optional>

/**
 * @brief Creates a formatted message with game mode, player, board state, and optional position.
 *
 * Combines the provided game mode, player symbol, board state, and optional row and column
 * into a single string message. If row and column are provided, they are included in the message.
 *
 * @param gameMode The game mode identifier (e.g., human vs AI).
 * @param player The current player symbol ('X' or 'O').
 * @param boardState The serialized board state as a string.
 * @param row Optional row index for the move.
 * @param col Optional column index for the move.
 * @return std::string A formatted message string with the game information.
 */
std::string createMessage(int gameMode, char player, const std::string& boardState, 
                          std::optional<int> row, std::optional<int> col) {
    std::string message = std::to_string(gameMode) + " " + std::string(1, player) + " " + boardState;
    
    if (row.has_value() && col.has_value()) {
        message += " " + std::to_string(row.value()) + " " + std::to_string(col.value());
    }

    return message;
}