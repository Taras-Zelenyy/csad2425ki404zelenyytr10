#include "gtest/gtest.h"
#include "../include/player.h"

class PlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = PLAYER_X;
    }
};

// Test initial player state
TEST_F(PlayerTest, InitialPlayerState) {
    ASSERT_EQ(player, PLAYER_X);
}

// Test switchPlayer function
TEST_F(PlayerTest, SwitchPlayer) {
    switchPlayer();
    ASSERT_EQ(player, PLAYER_O);

    switchPlayer();
    ASSERT_EQ(player, PLAYER_X);
}

// Test multiple switches
TEST_F(PlayerTest, MultipleSwitches) {
    for (int i = 0; i < 10; ++i) {
        char expectedPlayer = (i % 2 == 0) ? PLAYER_O : PLAYER_X;
        switchPlayer();
        ASSERT_EQ(player, expectedPlayer);
    }
}