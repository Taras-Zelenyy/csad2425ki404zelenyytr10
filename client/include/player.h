/// Represents the current player, either PLAYER_X or PLAYER_O.
extern char player;

/// Symbol representing player X.
const char PLAYER_X = 'X';

/// Symbol representing player O.
const char PLAYER_O = 'O';

/**
 * @brief Switches the current player.
 *
 * Toggles the `player` variable between PLAYER_X and PLAYER_O,
 * allowing players to alternate turns.
 */
void switchPlayer();