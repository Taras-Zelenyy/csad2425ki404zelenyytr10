#include <gtest/gtest.h>
#include "../include/server_logic.h"

TEST(ServerLogicTests, ParseBoard) {
    char board[BOARD_SIZE][BOARD_SIZE];
    std::string input = "XO XO OX ";
    parseBoard(input, board);

    EXPECT_EQ(board[0][0], 'X');
    EXPECT_EQ(board[0][1], 'O');
    EXPECT_EQ(board[0][2], ' ');
    EXPECT_EQ(board[1][0], 'X');
    EXPECT_EQ(board[1][1], 'O');
    EXPECT_EQ(board[1][2], ' ');
    EXPECT_EQ(board[2][0], 'O');
    EXPECT_EQ(board[2][1], 'X');
    EXPECT_EQ(board[2][2], ' ');
}

TEST(ServerLogicTests, BoardToString) {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', ' '},
        {'X', 'O', ' '},
        {'O', 'X', ' '}
    };
    std::string result = boardToString(board);
    EXPECT_EQ(result, "XO XO OX ");
}

TEST(ServerLogicTests, IsValidMove) {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', ' '},
        {'X', 'O', ' '},
        {'O', 'X', ' '}
    };
    EXPECT_TRUE(isValidMove(board, 0, 2));
    EXPECT_FALSE(isValidMove(board, 0, 0));
    EXPECT_FALSE(isValidMove(board, 1, 1));
    EXPECT_FALSE(isValidMove(board, -1, 0)); // Out of bounds
    EXPECT_FALSE(isValidMove(board, 3, 3));  // Out of bounds
}

TEST(ServerLogicTests, CheckWin) {
    char boardWinRow[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'X', 'X'},
        {'O', 'O', ' '},
        {' ', ' ', ' '}
    };
    char boardWinCol[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', ' '},
        {'X', 'O', ' '},
        {'X', ' ', ' '}
    };
    char boardWinDiag[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', ' '},
        {'O', 'X', ' '},
        {' ', ' ', 'X'}
    };
    char boardNoWin[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', ' '},
        {'O', 'X', ' '},
        {' ', ' ', 'O'}
    };

    EXPECT_TRUE(checkWin(boardWinRow, PLAYER_X));
    EXPECT_TRUE(checkWin(boardWinCol, PLAYER_X));
    EXPECT_TRUE(checkWin(boardWinDiag, PLAYER_X));
    EXPECT_FALSE(checkWin(boardNoWin, PLAYER_X));
}

TEST(ServerLogicTests, IsBoardFull) {
    char fullBoard[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'O', 'X', 'O'}
    };
    char notFullBoard[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'O', ' '},
        {'O', 'X', 'O'},
        {'O', 'X', 'O'}
    };

    EXPECT_TRUE(isBoardFull(fullBoard));
    EXPECT_FALSE(isBoardFull(notFullBoard));
}

TEST(ServerLogicTests, Opponent) {
    EXPECT_EQ(opponent(PLAYER_X), PLAYER_O);
    EXPECT_EQ(opponent(PLAYER_O), PLAYER_X);
}

TEST(ServerLogicTests, BestMove) {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'X', 'X', 'O'},
        {'X', 'O', ' '},
        {' ', ' ', ' '}
    };
    int move[2];
    bestMove(board, PLAYER_X, move);

    // Best move is at (2, 2) for PLAYER_X to block or win
    EXPECT_EQ(move[0], 2);
    EXPECT_EQ(move[1], 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}