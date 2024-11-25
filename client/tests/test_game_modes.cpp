#include "gtest/gtest.h"
#include "../include/game_modes.h"
#include "../include/board.h"
#include "../include/player.h"

class GameModesTest : public ::testing::Test {
protected:
    void SetUp() override {
        resetBoard();
        player = PLAYER_X;
    }
};

// Test convertPositionToRowCol function
TEST_F(GameModesTest, ConvertPositionToRowCol) {
    Position pos = convertPositionToRowCol(1);
    ASSERT_EQ(pos.row, 0);
    ASSERT_EQ(pos.col, 0);

    pos = convertPositionToRowCol(5);
    ASSERT_EQ(pos.row, 1);
    ASSERT_EQ(pos.col, 1);

    pos = convertPositionToRowCol(9);
    ASSERT_EQ(pos.row, 2);
    ASSERT_EQ(pos.col, 2);
}
