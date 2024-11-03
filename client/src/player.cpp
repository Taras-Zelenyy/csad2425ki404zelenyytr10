#include "../include/player.h"

char player = PLAYER_X;

void switchPlayer() {
    player = (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}