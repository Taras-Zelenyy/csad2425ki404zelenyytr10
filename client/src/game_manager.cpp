#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/board.h"
#include "../include/game_modes.h"
#include "../include/communication.h"
#include "../include/console_utils.h"
#include "../include/game_manager.h"
#include "../include/player.h"
#include "../libs/pugixml.hpp"

/**
 * @brief Saves the current game state to an XML file.
 *
 * Serializes the game board and current player information to an XML file specified by `filename`.
 * Displays a success message if the game is saved successfully, or an error message if it fails.
 *
 * @param filename The name of the file to save the game state to.
 */
void saveGame(const std::string& filename) {
    pugi::xml_document doc;
    pugi::xml_node game = doc.append_child("Game");

    pugi::xml_node boardNode = game.append_child("Board");
    for (int i = 0; i < BOARD_SIZE; i++) {
        pugi::xml_node row = boardNode.append_child("Row");
        for (int j = 0; j < BOARD_SIZE; j++) {
            row.append_child("Cell").text() = std::string(1, board[i][j]).c_str();
        }
    }

    game.append_child("CurrentPlayer").text() = std::string(1, player).c_str();

    if (doc.save_file(filename.c_str())) {
        setConsoleColor(DARK_GRAY);
        std::cout << "[INFO] Game saved successfully in XML format.\n";
        setConsoleColor(LIGHT_GRAY);
    } else {
        setConsoleColor(LIGHT_RED);
        std::cerr << "[ERROR] Failed to save game.\n";
        setConsoleColor(LIGHT_GRAY);
    }
}


/**
 * @brief Loads the game state from an XML file.
 *
 * Reads the game board and current player information from the specified XML file to restore the game state.
 * Displays success or error messages based on the load result.
 *
 * @param filename The name of the file to load the game state from.
 * @return bool True if the game was successfully loaded, false otherwise.
 */
bool loadGame(const std::string& filename) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());

    if (!result) {
        setConsoleColor(LIGHT_RED);
        std::cerr << "[ERROR] Failed to load game: " << result.description() << "\n";
        setConsoleColor(LIGHT_GRAY);
        return false;
    }

    pugi::xml_node boardNode = doc.child("Game").child("Board");
    int row = 0;
    for (pugi::xml_node rowNode : boardNode.children("Row")) {
        int col = 0;
        for (pugi::xml_node cell : rowNode.children("Cell")) {
            board[row][col] = cell.text().as_string()[0];
            col++;
        }
        row++;
    }

    player = doc.child("Game").child("CurrentPlayer").text().as_string()[0];

    setConsoleColor(DARK_GRAY);
    std::cout << "[INFO] Game loaded successfully from XML.\n";
    setConsoleColor(LIGHT_GRAY);
    return true;
}

/**
 * @brief Initializes and starts a new game session.
 *
 * Resets the game board, sets the starting player, and prompts the user to select a game mode. Based on the selection,
 * it starts a game mode (e.g., human vs human, human vs AI). Sets up serial communication for game data exchange.
 */
void newGame() {
    resetBoard();
    player = PLAYER_X;
    clearConsole();

    int gameMode;
    std::cout << "Select Tic Tac Toe Mode:\n";
    std::cout << "1. Man vs Man\n";
    std::cout << "2. Man vs AI\n";
    std::cout << "3. AI vs AI\n";
    std::cout << "Enter your choice: ";
    std::cin >> gameMode;

    clearConsole();

    HANDLE hSerial = setupSerial("COM3");
    if (hSerial == INVALID_HANDLE_VALUE) {
        return;
    }

    switch (gameMode) {
        case MODE_MAN_VS_MAN:
            manVsMan(hSerial);
            break;
        case MODE_MAN_VS_AI:
            manVsAI(hSerial);
            break;
        case MODE_AI_VS_AI:
            aiVsAI(hSerial);
            break;
        default:
            setConsoleColor(LIGHT_RED);
            std::cerr << "[ERROR] Invalid game mode selected." << std::endl;
            setConsoleColor(LIGHT_GRAY);
            break;
    }

    CloseHandle(hSerial);
}