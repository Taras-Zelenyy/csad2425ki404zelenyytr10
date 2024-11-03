#include <string>

const int BOARD_SIZE = 3;
extern char board[BOARD_SIZE][BOARD_SIZE];

void displayBoard();
void updateBoard(int row, int col, char player);
void updateBoardFull(const std::string& boardStr);
void resetBoard();
std::string serializeBoard();