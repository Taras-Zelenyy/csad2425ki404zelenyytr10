#include <iostream>
#include "../include/communication.h"
#include "../include/console_utils.h"

/**
 * @brief Sends a message over the serial connection.
 *
 * Writes the specified message to the serial port. Displays a success message if the write operation
 * completes, or an error message if it fails.
 *
 * @param message The message to send.
 * @param hSerial The handle to the open serial connection.
 */
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

/**
 * @brief Receives a message from the serial connection.
 *
 * Reads data from the serial port into a buffer and returns the received data as a string.
 * Displays a message indicating the data received or an error if the read operation fails.
 *
 * @param hSerial The handle to the open serial connection.
 * @return std::string The received message, or an empty string if the read operation fails.
 */
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

/**
 * @brief Sets up a serial communication connection.
 *
 * Configures the serial port with standard parameters (9600 baud rate, 8 data bits, no parity, 1 stop bit)
 * and returns a handle to the connection. If an error occurs, an error message is displayed, and 
 * INVALID_HANDLE_VALUE is returned.
 *
 * @param portName The name of the COM port to connect to (e.g., "COM3").
 * @return HANDLE A handle to the opened serial connection, or INVALID_HANDLE_VALUE if an error occurs.
 */
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
