#include <windows.h>
#include "../include/console_utils.h"

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void clearConsole() {
    system("cls");
}
