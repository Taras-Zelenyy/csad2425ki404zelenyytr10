#include <iostream>
#include "../include/communication.h"
#include "../include/console_utils.h"

void sendMessage(const std::string &message, HANDLE &hSerial) {
    DWORD bytesSent;
    if (!WriteFile(hSerial, message.c_str(), message.size(), &bytesSent, NULL)) {
        setConsoleColor(LIGHT_RED);
        std::cerr << "[ERROR] Failed to send message.\n";
        setConsoleColor(LIGHT_GRAY);
    } else {
        setConsoleColor(DARK_GRAY);
        std::cout << "[INFO] Message sent to Arduino: " << message << std::endl;
        setConsoleColor(LIGHT_GRAY);
    }
    setConsoleColor(LIGHT_GRAY);
}

std::string receiveMessage(HANDLE &hSerial) {
    char buffer[128];
    DWORD bytesRead;
    if (!ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
        setConsoleColor(LIGHT_RED);
        std::cerr << "[ERROR] Failed to read from Arduino.\n";
        setConsoleColor(LIGHT_GRAY);
        return "";
    }
    std::string received(buffer, bytesRead);
    setConsoleColor(DARK_GRAY);
    std::cout << "[INFO] Message received from Arduino: " << received << std::endl;
    setConsoleColor(LIGHT_GRAY);
    return received;
}

HANDLE setupSerial(const std::string& portName) {
    HANDLE hSerial = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        setConsoleColor(LIGHT_RED);
        std::cerr << "[ERROR] Failed to open COM port.\n";
        setConsoleColor(LIGHT_GRAY);
        return INVALID_HANDLE_VALUE;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        setConsoleColor(LIGHT_RED);
        std::cerr << "[ERROR] Failed to get COM port state.\n";
        setConsoleColor(LIGHT_GRAY);
        return INVALID_HANDLE_VALUE;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        setConsoleColor(LIGHT_RED);
        std::cerr << "[ERROR] Failed to set COM port state.\n";
        setConsoleColor(LIGHT_GRAY);
        return INVALID_HANDLE_VALUE;
    }
    setConsoleColor(LIGHT_GRAY);

    return hSerial;
}
