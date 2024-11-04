#include <windows.h>
#include <string>

const std::string SAVE_MODE = "save";
const std::string LOAD_MODE = "load";
const std::string NEW_MODE = "new";
const std::string CONFIG_PATH = "config/config.xml";

const std::string AI_PLAYER = "AI";
const std::string REAL_PLAYER = "PLAYER";

const std::string INVALIDE_MSG = "INVALID";
const std::string WIN_MSG = "WIN";
const std::string DRAW_MSG = "DRAW";
const std::string CONTINUE_MSG = "CONTINUE";

const int MODE_MAN_VS_MAN = 1;
const int MODE_MAN_VS_AI = 2;
const int MODE_AI_VS_AI = 3;

struct Position {
    int row;
    int col;
};

Position convertPositionToRowCol(int playerMove);

void manVsMan(HANDLE hSerial);
void manVsAI(HANDLE hSerial);
void aiVsAI(HANDLE hSerial);
