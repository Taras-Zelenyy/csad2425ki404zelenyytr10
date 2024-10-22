#include <iostream>
#include "../include/communication.h"

int main() {
    HANDLE hSerial = setupSerial("COM3");
    if (hSerial == INVALID_HANDLE_VALUE) {
        return 1;
    }

    std::string message;
    std::cout << "Enter your message: ";
    std::getline(std::cin, message);

    sendMessage(message, hSerial);
    receiveMessage(hSerial);

    CloseHandle(hSerial);
    system("pause"); 

    return 0;
}
