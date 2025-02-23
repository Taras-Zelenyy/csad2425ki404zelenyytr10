#include <iostream>
#include <string>

#include "../include/board.h"
#include "../include/communication.h"
#include "../include/format_message.h"
#include "../include/game_modes.h"
#include "../include/player.h"
#include "../include/console_utils.h"
#include "../include/game_manager.h"

/**
 * @brief Converts a player's move to a board position.
 *
 * Calculates the row and column of the board based on a player's move input (1-9).
 *
 * @param playerMove The move input by the player (1-9).
 * @return Position The corresponding row and column on the board.
 */
Position convertPositionToRowCol(int playerMove) {
    Position pos;
    pos.row = (playerMove - 1) / BOARD_SIZE;
    pos.col = (playerMove - 1) % BOARD_SIZE;
    return pos;
}


/**
 * @brief Prompts the player for a valid move and processes special commands.
 *
 * Accepts user input for moves and handles special commands for saving, loading, and restarting the game.
 *
 * @param player The current player symbol ('X' or 'O').
 * @return int The valid player move as an integer.
 */
int getValidMove(char player) {
    std::string input;
    int playerMove;

    while (true) {
        std::cout << "Player " << player << " enter your move (1-9) or command (save, load, new): ";
        std::cin >> input;

        if (input == SAVE_MODE) {
            saveGame(CONFIG_PATH);
            continue;
        } else if (input == LOAD_MODE) {
            loadGame(CONFIG_PATH);
            displayBoard();
            continue;
        } else if (input == NEW_MODE) {
            newGame();
            displayBoard();
            continue;
        }

        bool isInteger = true;
        for (char c : input) {
            if (!std::isdigit(c)) {
                isInteger = false;
                break;
            }
        }

        if (isInteger) {
            playerMove = std::stoi(input);
            break;
        } else {
            setConsoleColor(LIGHT_RED);
            std::cout << "\n[ERROR] Invalid input. Please enter a valid integer or correct command.\n" << std::endl;
            setConsoleColor(LIGHT_GRAY);
        }
    }

    return playerMove;
}

/**
 * @brief Handles the human vs human game mode.
 *
 * Manages gameplay where both players are human, handling move inputs,
 * board updates, and game end conditions.
 *
 * @param hSerial Handle to the communication port for sending and receiving game data.
 */
void manVsMan(HANDLE hSerial) {
    displayBoard();
    while (true) {
        int playerMove = getValidMove(player);

        Position pos = convertPositionToRowCol(playerMove);
        int row = pos.row;
        int col = pos.col;

        std::string message = createMessage(MODE_MAN_VS_MAN, player, serializeBoard(), row, col);
        sendMessage(message, hSerial);

        std::string response = receiveMessage(hSerial);

        if (response.find(WIN_MSG) != std::string::npos) {
            updateBoard(row, col, player);
            displayBoard();
            setConsoleColor(LIGHT_YELLOW);
            std::cout << "Player " << player << " wins!" << std::endl;
            setConsoleColor(LIGHT_GRAY);
            break;
        } else if (response.find(DRAW_MSG) != std::string::npos) {
            updateBoard(row, col, player);
            displayBoard();
            setConsoleColor(LIGHT_YELLOW);
            std::cout << "The game is a draw!" << std::endl;
            setConsoleColor(LIGHT_GRAY);
            break;
        } else if (response.find(INVALIDE_MSG) != std::string::npos) {
            setConsoleColor(LIGHT_RED);
            std::cout << "[ERROR] Invalid move sent to server. Try again." << std::endl;
            setConsoleColor(LIGHT_GRAY);
            continue;
        } else {
            updateBoard(row, col, player);
            displayBoard();
        }

        switchPlayer();
    }
}

/**
 * @brief Handles the human vs AI game mode.
 *
 * Manages gameplay where one player is human and the other is AI,
 * handling moves, board updates, and game end conditions.
 *
 * @param hSerial Handle to the communication port for sending and receiving game data.
 */
void manVsAI(HANDLE hSerial) {
    displayBoard();
    while (true) {
        int playerMove = getValidMove(player);

        Position pos = convertPositionToRowCol(playerMove);
        int row = pos.row;
        int col = pos.col;

        std::string message = createMessage(MODE_MAN_VS_AI, player, serializeBoard(), row, col);
        sendMessage(message, hSerial);

        std::string response = receiveMessage(hSerial);

        if (response.find(INVALIDE_MSG) != std::string::npos) {
            setConsoleColor(LIGHT_RED);
            std::cout << "[ERROR] Invalid move sent to server. Try again." << std::endl;
            setConsoleColor(LIGHT_GRAY);
            continue;
        } else {
            std::string boardStateStr = response.substr(0, 9);
            updateBoardFull(boardStateStr);

            if (response.find(WIN_MSG + "_" + REAL_PLAYER) != std::string::npos) {
                displayBoard();
                setConsoleColor(LIGHT_YELLOW);
                std::cout << "You win!" << std::endl;
                setConsoleColor(LIGHT_GRAY);
                break;
            } else if (response.find(WIN_MSG + "_" + AI_PLAYER) != std::string::npos) {
                displayBoard();
                setConsoleColor(LIGHT_YELLOW);
                std::cout << "AI wins!" << std::endl;
                setConsoleColor(LIGHT_GRAY);
                break;
            } else if (response.find(DRAW_MSG) != std::string::npos) {
                displayBoard();
                setConsoleColor(LIGHT_YELLOW);
                std::cout << "The game is a draw!" << std::endl;
                setConsoleColor(LIGHT_GRAY);
                break;
            } else if (response.find(CONTINUE_MSG) != std::string::npos) {
                displayBoard();
                continue;
            } else {
                setConsoleColor(LIGHT_RED);
                std::cerr << "[ERROR] Unrecognized response from server: " << response << std::endl;
                setConsoleColor(LIGHT_GRAY);
            }
        }
    }
}

/**
 * @brief Handles the AI vs AI game mode.
 *
 * Manages gameplay where both players are AI, automating moves and handling game end conditions.
 *
 * @param hSerial Handle to the communication port for sending and receiving game data.
 */
void aiVsAI(HANDLE hSerial) {
    displayBoard();
    while (true) {
        std::string message = createMessage(MODE_AI_VS_AI, player, serializeBoard());
        sendMessage(message, hSerial);

        std::string response = receiveMessage(hSerial);
        std::string boardStateStr = response.substr(0, 9);
        updateBoardFull(boardStateStr);
        displayBoard();

        if (response.find(WIN_MSG + "_" + PLAYER_X) != std::string::npos) {
            setConsoleColor(LIGHT_YELLOW);
            std::cout << "AI 'X' wins!" << std::endl;
            setConsoleColor(LIGHT_GRAY);
            break;
        } else if (response.find(WIN_MSG + "_" + PLAYER_O) != std::string::npos) {
            setConsoleColor(LIGHT_YELLOW);
            std::cout << "AI 'O' wins!" << std::endl;
            setConsoleColor(LIGHT_GRAY);
            break;
        } else if (response.find(DRAW_MSG) != std::string::npos) {
            setConsoleColor(LIGHT_YELLOW);
            std::cout << "The game is a draw!" << std::endl;
            setConsoleColor(LIGHT_GRAY);
            break;
        } else if (response.find(CONTINUE_MSG) != std::string::npos) {
            switchPlayer();
            continue;
        } else {
            setConsoleColor(LIGHT_RED);
            std::cerr << "[ERROR] Unrecognized response from server: " << response << std::endl;
            setConsoleColor(LIGHT_GRAY);
        }
    }
}
