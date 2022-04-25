// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

#ifndef _WIN32

void ScreenConsoleLinux::ClrScr()
{
    system("clear");
}

void ScreenConsoleLinux::GotoXY(double x, double y)
{
    printf("\033[%d;%dH", (int)y + 1, (int)x + 1);
}

uint16_t ScreenConsoleLinux::GetMaxX()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

uint16_t ScreenConsoleLinux::GetMaxY()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

void ScreenConsoleLinux::SetColor(ConsoleColor color)
{
    std::cout << "\033[" << color << "m";
}

void ScreenConsoleLinux::Draw(const std::string& str)
{
    std::cout << str;
}

void ScreenConsoleLinux::Draw(uint16_t x, uint16_t y, const std::string& str)
{
    GotoXY(x, y);
    Draw(str);
}

void ScreenConsoleLinux::Draw(uint16_t x, uint16_t y, char str)
{
    GotoXY(x, y);
    std::string s(1, str);
    Draw(s);
}

#endif
