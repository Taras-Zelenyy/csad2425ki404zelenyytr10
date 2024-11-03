@echo off

set CLIENT_PATH="%~dp0client\src\client.cpp"
set SRC_PATH="%~dp0client\src"
set INC_PATH="%~dp0client\include"
set SERVER_PATH="%~dp0server\server.ino"
set LIB_PATH="%~dp0libs"

echo ===================================
echo [INFO] Checking for Arduino CLI...
if not exist arduino-cli.exe (
    echo [INFO] Arduino CLI not found. Downloading...
    curl -fsSL https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.zip -o arduino-cli.zip
    if %errorlevel% neq 0 (
        echo [ERROR] Failed to download Arduino CLI.
        pause
        exit /b %errorlevel%
    )
    tar -xf arduino-cli.zip
    if %errorlevel% neq 0 (
        echo [ERROR] Failed to extract Arduino CLI.
        pause
        exit /b %errorlevel%
    )
    del arduino-cli.zip
    echo [INFO] Arduino CLI downloaded successfully.
) else (
    echo [INFO] Arduino CLI found.
)

echo ===================================
echo [INFO] Compiling client code...
if not exist %CLIENT_PATH% (
    echo [ERROR] Client source file not found: %CLIENT_PATH%
    pause
    exit /b 1
)

g++ -I%INC_PATH% -I%LIB_PATH% %CLIENT_PATH% %SRC_PATH%\board.cpp %SRC_PATH%\communication.cpp %SRC_PATH%\format_message.cpp %SRC_PATH%\game_modes.cpp %SRC_PATH%\console_utils.cpp %SRC_PATH%\game_manager.cpp %SRC_PATH%\player.cpp %LIB_PATH%\pugixml.cpp -o client.exe
if %errorlevel% neq 0 (
    echo [ERROR] Failed to compile client code.
    pause
    exit /b %errorlevel%
)
echo [INFO] Client compiled successfully.

echo ===================================
echo [INFO] Compiling server code...
if not exist %SERVER_PATH% (
    echo [ERROR] Server source file not found: %SERVER_PATH%
    pause
    exit /b 1
)
arduino-cli.exe compile --fqbn arduino:avr:nano %SERVER_PATH%
if %errorlevel% neq 0 (
    echo [ERROR] Failed to compile server code.
    pause
    exit /b %errorlevel%
)
echo [INFO] Server code compiled successfully.

echo ===================================
echo [INFO] Uploading server code to Arduino...
arduino-cli.exe upload -p COM3 --fqbn arduino:avr:nano %SERVER_PATH%
if %errorlevel% neq 0 (
    echo [ERROR] Failed to upload server code to Arduino.
    pause
    exit /b %errorlevel%
)
echo [INFO] Server code uploaded successfully.

echo ===================================
echo [INFO] Deleting Arduino CLI files...

rem Remove the arduino-cli executable if it was downloaded
if exist arduino-cli.exe (
    del arduino-cli.exe
    echo [INFO] arduino-cli.exe executable deleted.
)

rem Remove the LICENSE.txt if it was downloaded
if exist LICENSE.txt (
    del LICENSE.txt
    echo [INFO] LICENSE.txt deleted.
)

echo ===================================
echo [INFO] All tasks completed successfully.
pause
