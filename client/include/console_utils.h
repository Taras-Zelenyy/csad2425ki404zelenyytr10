/**
 * @enum ConsoleColor
 * @brief Defines color codes for console text.
 *
 * Provides color codes that can be used with `setConsoleColor` to change the text color
 * in the console output.
 */
enum ConsoleColor {
    BLACK = 0,         ///< Black color.
    DARK_BLUE = 1,     ///< Dark blue color.
    DARK_GREEN = 2,    ///< Dark green color.
    DARK_CYAN = 3,     ///< Dark cyan color.
    DARK_RED = 4,      ///< Dark red color.
    DARK_MAGENTA = 5,  ///< Dark magenta color.
    DARK_YELLOW = 6,   ///< Dark yellow color.
    LIGHT_GRAY = 7,    ///< Light gray color.
    DARK_GRAY = 8,     ///< Dark gray color.
    LIGHT_BLUE = 9,    ///< Light blue color.
    LIGHT_GREEN = 10,  ///< Light green color.
    LIGHT_CYAN = 11,   ///< Light cyan color.
    LIGHT_RED = 12,    ///< Light red color.
    LIGHT_MAGENTA = 13,///< Light magenta color.
    LIGHT_YELLOW = 14, ///< Light yellow color.
    WHITE = 15         ///< White color.
};

/**
 * @brief Sets the console text color.
 *
 * Changes the color of text in the console to the specified color code.
 *
 * @param color The color code from `ConsoleColor` to set for the console text.
 */
void setConsoleColor(int color);

/**
 * @brief Clears the console screen.
 *
 * Clears the console screen by issuing a system command.
 */
void clearConsole();