#include "../include/player.h"

/// Initializes the current player to PLAYER_X at the start of the game.
char player = PLAYER_X;

/**
 * @brief Switches the current player.
 *
 * Changes the `player` variable from PLAYER_X to PLAYER_O or vice versa,
 * allowing for alternating player turns.
 */
void switchPlayer() {
    player = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}