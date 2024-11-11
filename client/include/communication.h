#include <string>
#include <windows.h>

/**
 * @brief Sets up a serial communication connection.
 *
 * Opens a serial connection to the specified port, configuring the communication parameters.
 *
 * @param portName The name of the COM port to connect to (e.g., "COM3").
 * @return HANDLE A handle to the opened serial connection, or INVALID_HANDLE_VALUE if an error occurs.
 */
HANDLE setupSerial(const std::string& portName);

/**
 * @brief Sets up a serial communication connection.
 *
 * Opens a serial connection to the specified port, configuring the communication parameters.
 *
 * @param portName The name of the COM port to connect to (e.g., "COM3").
 * @return HANDLE A handle to the opened serial connection, or INVALID_HANDLE_VALUE if an error occurs.
 */
void sendMessage(const std::string &message, HANDLE &hSerial);

/**
 * @brief Receives a message from the serial connection.
 *
 * Reads data from the connected device via the serial port and returns it as a string.
 *
 * @param hSerial The handle to the open serial connection.
 * @return std::string The received message.
 */
std::string receiveMessage(HANDLE &hSerial);