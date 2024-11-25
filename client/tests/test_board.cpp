
#include "gtest/gtest.h"
#include "../include/board.h"

// Test fixture for board-related tests
class BoardTest : public ::testing::Test {
protected:
    void SetUp() override {
        resetBoard(); // Ensure board starts in a clean state
    }
};

// Test resetBoard function
TEST_F(BoardTest, ResetBoardInitializesCorrectly) {
    resetBoard();
    char expected[BOARD_SIZE][BOARD_SIZE] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' } };
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            ASSERT_EQ(board[i][j], expected[i][j]);
        }
    }
}

// Test updateBoard function
TEST_F(BoardTest, UpdateBoardUpdatesCorrectCell) {
    updateBoard(0, 0, 'X');
    ASSERT_EQ(board[0][0], 'X');
    updateBoard(1, 1, 'O');
    ASSERT_EQ(board[1][1], 'O');
}

// Test updateBoardFull function with valid input
TEST_F(BoardTest, UpdateBoardFullValidString) {
    std::string validBoard = "XO XO XO ";
    updateBoardFull(validBoard);
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            ASSERT_EQ(board[i][j], validBoard[index++]);
        }
    }
}

// Test updateBoardFull function with invalid input
TEST_F(BoardTest, UpdateBoardFullInvalidString) {
    std::string invalidBoard = "XO XO";
    testing::internal::CaptureStderr();
    updateBoardFull(invalidBoard);
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_TRUE(output.find("Invalid board string length") != std::string::npos);
}

// Test serializeBoard function
TEST_F(BoardTest, SerializeBoardReturnsCorrectString) {
    resetBoard();
    std::string serialized = serializeBoard();
    ASSERT_EQ(serialized, "123456789");
    updateBoard(0, 0, 'X');
    serialized = serializeBoard();
    ASSERT_EQ(serialized[0], 'X');
}

// Test displayBoard function (basic sanity check to ensure it runs without crashing)
TEST_F(BoardTest, DisplayBoardDoesNotCrash) {
    EXPECT_NO_THROW(displayBoard());
}
