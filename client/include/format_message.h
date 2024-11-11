#include <string>
#include <optional>

/**
 * @brief Creates a formatted message containing game mode, player, board state, and optional move position.
 *
 * Generates a string representing the current game state and player action, with optional row and column
 * coordinates for the move position.
 *
 * @param gameMode The game mode identifier (e.g., human vs AI).
 * @param player The current player symbol ('X' or 'O').
 * @param boardState The serialized board state as a string.
 * @param row Optional row index for the move.
 * @param col Optional column index for the move.
 * @return std::string A formatted message string containing the game information.
 */
std::string createMessage(
    int gameMode,
    char player,
    const std::string& boardState,
    std::optional<int> row = std::nullopt, 
    std::optional<int> col = std::nullopt
);
