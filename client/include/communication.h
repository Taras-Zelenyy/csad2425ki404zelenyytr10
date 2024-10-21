#include <string>
#include <windows.h>

void sendMessage(const std::string &message, HANDLE &hSerial);
std::string receiveMessage(HANDLE &hSerial);
HANDLE setupSerial(const std::string& portName);
