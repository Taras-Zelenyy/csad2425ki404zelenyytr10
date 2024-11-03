#include <string>
#include <windows.h>

HANDLE setupSerial(const std::string& portName);
void sendMessage(const std::string &message, HANDLE &hSerial);
std::string receiveMessage(HANDLE &hSerial);