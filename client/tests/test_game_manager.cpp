#include "gtest/gtest.h"
#include "../include/game_manager.h"
#include "../include/board.h"
#include "../include/player.h"
#include <fstream>

// Test fixture for game manager tests
class GameManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        resetBoard();
        player = PLAYER_X;
    }

    void TearDown() override {
        // Cleanup test files
        std::remove("test_save.xml");
    }
};

// Test saveGame function
TEST_F(GameManagerTest, SaveGameCreatesValidFile) {
    saveGame("test_save.xml");
    std::ifstream file("test_save.xml");
    ASSERT_TRUE(file.is_open()) << "File should exist after saveGame call.";
    file.close();
}

// Test saveGame content correctness
TEST_F(GameManagerTest, SaveGameContentCheck) {
    updateBoard(0, 0, PLAYER_X);
    updateBoard(1, 1, PLAYER_O);

    saveGame("test_save.xml");

    std::ifstream file("test_save.xml");
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    ASSERT_TRUE(content.find("<Cell>X</Cell>") != std::string::npos);
    ASSERT_TRUE(content.find("<Cell>O</Cell>") != std::string::npos);
}

// Test loadGame with a valid file
TEST_F(GameManagerTest, LoadGameWithValidFile) {
    updateBoard(0, 0, PLAYER_X);
    updateBoard(1, 1, PLAYER_O);

    saveGame("test_save.xml");
    resetBoard();

    bool result = loadGame("test_save.xml");
    ASSERT_TRUE(result) << "loadGame should succeed with a valid file.";
    ASSERT_EQ(board[0][0], PLAYER_X);
    ASSERT_EQ(board[1][1], PLAYER_O);
}

// Test loadGame with an invalid file
TEST_F(GameManagerTest, LoadGameWithInvalidFile) {
    bool result = loadGame("non_existent.xml");
    ASSERT_FALSE(result) << "loadGame should fail with a non-existent file.";
}

// Test newGame initialization
TEST_F(GameManagerTest, NewGameInitializesCorrectly) {
    // Simulate starting a new game
    resetBoard();
    newGame();

    // Check initial state of the board and player
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            ASSERT_EQ(board[i][j], '1' + (i * BOARD_SIZE + j));
        }
    }
    ASSERT_EQ(player, PLAYER_X);
}