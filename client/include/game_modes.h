#include <windows.h>
#include <string>

/// Represents the save command for the game state.
const std::string SAVE_MODE = "save";

/// Represents the load command to retrieve the game state.
const std::string LOAD_MODE = "load";

/// Represents the command to start a new game.
const std::string NEW_MODE = "new";

/// Path to the configuration file for saving/loading the game.
const std::string CONFIG_PATH = "config/config.xml";

/// Represents an AI-controlled player.
const std::string AI_PLAYER = "AI";

/// Represents a human-controlled player.
const std::string REAL_PLAYER = "PLAYER";

/// Message indicating an invalid move.
const std::string INVALIDE_MSG = "INVALID";

/// Message indicating a winning condition.
const std::string WIN_MSG = "WIN";

/// Message indicating a draw condition.
const std::string DRAW_MSG = "DRAW";

/// Message indicating the game should continue.
const std::string CONTINUE_MSG = "CONTINUE";

/// Game mode where both players are human.
const int MODE_MAN_VS_MAN = 1;

/// Game mode with one human and one AI player.
const int MODE_MAN_VS_AI = 2;

/// Game mode with both players as AI.
const int MODE_AI_VS_AI = 3;

/**
 * @struct Position
 * @brief Represents a position on the game board.
 */
struct Position {
    int row; ///< Row index of the position.
    int col; ///< Column index of the position.
};

/**
 * @brief Converts a player's move to a board position.
 * 
 * @param playerMove The move input by the player (1-9).
 * @return Position The corresponding row and column on the board.
 */
Position convertPositionToRowCol(int playerMove);

/**
 * @brief Starts a human vs human game mode.
 * 
 * @param hSerial Handle to the communication port for sending and receiving game data.
 */
void manVsMan(HANDLE hSerial);

/**
 * @brief Starts a human vs AI game mode.
 * 
 * @param hSerial Handle to the communication port for sending and receiving game data.
 */
void manVsAI(HANDLE hSerial);

/**
 * @brief Starts an AI vs AI game mode.
 * 
 * @param hSerial Handle to the communication port for sending and receiving game data.
 */
void aiVsAI(HANDLE hSerial);
