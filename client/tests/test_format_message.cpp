#include "gtest/gtest.h"
#include "../include/format_message.h"

// Test createMessage function with only required parameters
TEST(FormatMessageTest, CreateMessageWithRequiredParameters) {
    std::string boardState = "XO3XO6XO9";
    std::string message = createMessage(1, 'X', boardState);
    ASSERT_EQ(message, "1 X XO3XO6XO9");
}

// Test createMessage function with all parameters including row and col
TEST(FormatMessageTest, CreateMessageWithAllParameters) {
    std::string boardState = "XO3XO6XO9";
    std::string message = createMessage(2, 'O', boardState, 1, 2);
    ASSERT_EQ(message, "2 O XO3XO6XO9 1 2");
}

// Test createMessage function with missing row and col (optional values)
TEST(FormatMessageTest, CreateMessageWithNoOptionalParameters) {
    std::string boardState = "123456789";
    std::string message = createMessage(0, 'O', boardState);
    ASSERT_EQ(message, "0 O 123456789");
}