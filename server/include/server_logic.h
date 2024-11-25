// #include <Arduino.h>

#ifdef TEST_ENVIRONMENT
#include "mock_arduino.h"
#else
#include <Arduino.h>
#endif


const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const int BOARD_SIZE = 3;

void parseBoard(const String &input, char board[BOARD_SIZE][BOARD_SIZE]);
String boardToString(char board[BOARD_SIZE][BOARD_SIZE]);
bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
bool checkWin(char board[BOARD_SIZE][BOARD_SIZE], char player);
bool isBoardFull(char board[BOARD_SIZE][BOARD_SIZE]);
char opponent(char player);
int minimax(char board[BOARD_SIZE][BOARD_SIZE], char currentPlayer, char aiPlayer, int depth);
void bestMove(char board[BOARD_SIZE][BOARD_SIZE], char aiPlayer, int move[2]);