#include <windows.h>
#include "../include/console_utils.h"

/**
 * @brief Sets the console text color.
 *
 * Changes the color of text in the console to the specified color code.
 *
 * @param color The color code from `ConsoleColor` to set for the console text.
 */
void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

/**
 * @brief Clears the console screen.
 *
 * Executes a system command to clear the console screen.
 */
void clearConsole() {
    system("cls");
}
