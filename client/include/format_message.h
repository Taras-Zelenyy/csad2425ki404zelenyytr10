#include <string>
#include <optional>

std::string createMessage(
    int gameMode,
    char player,
    const std::string& boardState,
    std::optional<int> row = std::nullopt, 
    std::optional<int> col = std::nullopt
);
