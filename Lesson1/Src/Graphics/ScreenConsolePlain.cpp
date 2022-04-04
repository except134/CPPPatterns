// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

#ifdef _WIN32

void ScreenConsolePlain::ClrScr()
{
    system("cls");
}

void ScreenConsolePlain::GotoXY(double x, double y)
{
    const COORD cc = { short(x), short(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
}

uint16_t ScreenConsolePlain::GetMaxX()
{
    HANDLE hWndConsole;
    if(hWndConsole = GetStdHandle(STD_ERROR_HANDLE)) {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if(GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
            return consoleInfo.srWindow.Right;
            int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
    }

    return 0;
}

uint16_t ScreenConsolePlain::GetMaxY()
{
    HANDLE hWndConsole;
    if(hWndConsole = GetStdHandle(STD_ERROR_HANDLE)) {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if(GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
            return consoleInfo.srWindow.Bottom;
        }
    }

    return 0;
}

void ScreenConsolePlain::SetColor(ConsoleColor color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
}

void ScreenConsolePlain::Draw(const std::string& str)
{
    std::cout << str;
}


#endif
