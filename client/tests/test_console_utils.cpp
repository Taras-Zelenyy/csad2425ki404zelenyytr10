#include "gtest/gtest.h"
#include "../include/console_utils.h"
#include <windows.h>

// Test setConsoleColor function
TEST(ConsoleUtilsTest, SetConsoleColorDoesNotCrash) {
    for (int color = 0; color <= 15; ++color) {
        EXPECT_NO_THROW(setConsoleColor(color));
    }
}

// Test clearConsole function
TEST(ConsoleUtilsTest, ClearConsoleDoesNotCrash) {
    EXPECT_NO_THROW(clearConsole());
}