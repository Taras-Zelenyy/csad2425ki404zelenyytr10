#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/communication.h"

// Mock for Serial Communication
class MockSerialCommunication {
public:
    MOCK_METHOD(HANDLE, CreateFile, (const std::string& portName), ());
    MOCK_METHOD(bool, WriteFile, (HANDLE hSerial, const std::string& message), ());
    MOCK_METHOD(std::string, ReadFile, (HANDLE hSerial), ());
    MOCK_METHOD(bool, SetCommState, (HANDLE hSerial), ());
    MOCK_METHOD(bool, GetCommState, (HANDLE hSerial), ());
};

// Updated functions to accept mock objects
HANDLE setupSerial(const std::string& portName, MockSerialCommunication& mockComm) {
    HANDLE hSerial = mockComm.CreateFile(portName);
    if (hSerial == INVALID_HANDLE_VALUE) return hSerial;

    if (!mockComm.GetCommState(hSerial)) {
        return INVALID_HANDLE_VALUE;
    }

    if (!mockComm.SetCommState(hSerial)) {
        return INVALID_HANDLE_VALUE;
    }

    return hSerial;
}

void sendMessage(const std::string& message, HANDLE hSerial, MockSerialCommunication& mockComm) {
    if (!mockComm.WriteFile(hSerial, message)) {
        throw std::runtime_error("Failed to send message.");
    }
}

std::string receiveMessage(HANDLE hSerial, MockSerialCommunication& mockComm) {
    return mockComm.ReadFile(hSerial);
}

// Tests
class CommunicationTest : public ::testing::Test {
protected:
    MockSerialCommunication mockComm;
};

// Test: Successful setup of a serial connection
TEST_F(CommunicationTest, SetupSerialSuccess) {
    EXPECT_CALL(mockComm, CreateFile("COM3"))
        .WillOnce(::testing::Return(reinterpret_cast<HANDLE>(1))); // Fake valid HANDLE
    EXPECT_CALL(mockComm, GetCommState(::testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockComm, SetCommState(::testing::_)).WillOnce(::testing::Return(true));

    HANDLE hSerial = setupSerial("COM3", mockComm);
    ASSERT_NE(hSerial, INVALID_HANDLE_VALUE);
}

// Test: Failed setup of a serial connection
TEST_F(CommunicationTest, SetupSerialFailure) {
    EXPECT_CALL(mockComm, CreateFile("COM3"))
        .WillOnce(::testing::Return(INVALID_HANDLE_VALUE)); // Simulate failure

    HANDLE hSerial = setupSerial("COM3", mockComm);
    ASSERT_EQ(hSerial, INVALID_HANDLE_VALUE);
}

// Test: Successful message sending over serial connection
TEST_F(CommunicationTest, SendMessageSuccess) {
    HANDLE fakeHandle = reinterpret_cast<HANDLE>(1); // Fake valid HANDLE

    EXPECT_CALL(mockComm, WriteFile(fakeHandle, "Hello"))
        .WillOnce(::testing::Return(true)); // Simulate successful write

    EXPECT_NO_THROW(sendMessage("Hello", fakeHandle, mockComm));
}

// Test: Failed message sending over serial connection
TEST_F(CommunicationTest, SendMessageFailure) {
    HANDLE fakeHandle = reinterpret_cast<HANDLE>(1); // Fake valid HANDLE

    EXPECT_CALL(mockComm, WriteFile(fakeHandle, "Hello"))
        .WillOnce(::testing::Return(false)); // Simulate failed write

    EXPECT_THROW(sendMessage("Hello", fakeHandle, mockComm), std::runtime_error);
}

// Test: Successful message receiving over serial connection
TEST_F(CommunicationTest, ReceiveMessageSuccess) {
    HANDLE fakeHandle = reinterpret_cast<HANDLE>(1); // Fake valid HANDLE

    EXPECT_CALL(mockComm, ReadFile(fakeHandle))
        .WillOnce(::testing::Return("ReceivedMessage")); // Simulate successful read

    std::string message = receiveMessage(fakeHandle, mockComm);
    ASSERT_EQ(message, "ReceivedMessage");
}

// Test: Failed message receiving over serial connection
TEST_F(CommunicationTest, ReceiveMessageFailure) {
    HANDLE fakeHandle = reinterpret_cast<HANDLE>(1); // Fake valid HANDLE

    EXPECT_CALL(mockComm, ReadFile(fakeHandle)).WillOnce(::testing::Return("")); // Simulate failed read

    std::string message = receiveMessage(fakeHandle, mockComm);
    ASSERT_EQ(message, "");
}