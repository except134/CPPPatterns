// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

//========================================================================================================================

int main(void)
{
    LoggerProxy::Instance().SetReal(&LoggerFile::Instance());
    LoggerProxy::Instance().OpenLogFile("log.txt");

    gScreen = &ScreenConsoleBuffered::Instance();

    SBomber game;

    do {
        game.TimeStart();

        if(_kbhit()) {
            game.ProcessKBHit();
        }

        gScreen->ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while(!game.GetExitFlag());

    return 0;
}
