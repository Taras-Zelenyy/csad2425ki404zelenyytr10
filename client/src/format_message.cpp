#include "../include/format_message.h"
#include <optional>

std::string createMessage(int gameMode, char player, const std::string& boardState, 
                          std::optional<int> row, std::optional<int> col) {
    std::string message = std::to_string(gameMode) + " " + std::string(1, player) + " " + boardState;
    
    if (row.has_value() && col.has_value()) {
        message += " " + std::to_string(row.value()) + " " + std::to_string(col.value());
    }

    return message;
}