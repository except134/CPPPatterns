// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

//========================================================================================================================

int main(void)
{
    LoggerProxy::Instance().SetReal(&LoggerFile::Instance());
    LoggerProxy::Instance().OpenLogFile("log.txt");

#ifdef _WIN32
    gScreen = &ScreenConsoleBuffered::Instance();
#else
    gScreen = &ScreenConsoleLinux::Instance();
#endif

    SBomber game;

    srand(time(0));

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
