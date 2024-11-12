#include <iostream>
#include <windows.h>

#include "../include/game_manager.h"

/**
 * @brief Main function of the game client.
 *
 * Initializes a new game session by calling the newGame() function
 * from the game manager module and pauses the program before exiting.
 *
 * @return int Program exit status.
 */
int main() {
    newGame();
    system("pause");
    return 0;
}