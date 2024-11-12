#include <string>

/**
 * @brief Starts a new game session.
 *
 * Initializes a new game, prompts the user to select a game mode, and manages game flow accordingly.
 */
void newGame();
/**
 * @brief Saves the current game state to a file.
 *
 * Serializes the game board and player information into an XML file.
 *
 * @param filename The name of the file to save the game state to.
 */
void saveGame(const std::string& filename);
/**
 * @brief Loads the game state from a file.
 *
 * Deserializes game data from an XML file to restore the game board and current player information.
 *
 * @param filename The name of the file to load the game state from.
 * @return bool True if the game was successfully loaded, false otherwise.
 */
bool loadGame(const std::string& filename);