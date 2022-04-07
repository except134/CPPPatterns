// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

#ifdef _WIN32

ScreenConsoleBuffered::ScreenConsoleBuffered()
{
    mOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    if(GetConsoleScreenBufferInfo(mOutputHandle, &consoleInfo)) {
        mWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
        mHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
    } else {
        mWidth = 100;
        mHeight = 50;

        SMALL_RECT windowSize = { 0, 0, static_cast<short>(mWidth) - 1, static_cast<short>(mHeight) - 1 };
        COORD bufferSize = { static_cast<short>(mWidth), static_cast<short>(mHeight) };

        SetConsoleWindowInfo(mOutputHandle, TRUE, &windowSize);
        SetConsoleScreenBufferSize(mOutputHandle, bufferSize);
    }

    consoleBuffer = std::make_unique<CHAR_INFO[]>(mWidth * mHeight);
    if(!consoleBuffer) {
        std::cerr << "Error! No memory!" << std::endl;
        _exit(1);
    }

    ZeroArray(consoleBuffer.get(), mWidth * mHeight);

    CONSOLE_CURSOR_INFO cci{ .bVisible = false };
    SetConsoleCursorInfo(mOutputHandle, &cci);
}

ScreenConsoleBuffered::~ScreenConsoleBuffered()
{
    CONSOLE_CURSOR_INFO cci{ .bVisible = true };
    SetConsoleCursorInfo(mOutputHandle, &cci);
}

void ScreenConsoleBuffered::ClrScr()
{
    for(size_t i = 0; i < mWidth * mHeight; ++i) {
        consoleBuffer[i].Char.AsciiChar = ' ';
        consoleBuffer[i].Attributes = 0;
    }
}

void ScreenConsoleBuffered::GotoXY(double x, double y)
{
    mCursor.X = static_cast<short>(x);
    mCursor.Y = static_cast<short>(y);
}

uint16_t ScreenConsoleBuffered::GetMaxX()
{
    return static_cast<uint16_t>(mWidth);
}

uint16_t ScreenConsoleBuffered::GetMaxY()
{
    return static_cast<uint16_t>(mHeight);
}

void ScreenConsoleBuffered::SetColor(ConsoleColor color)
{
    mCurColor = color;
}

void ScreenConsoleBuffered::Draw(const std::string& str)
{
    short x = mCursor.X, y = mCursor.Y;
    for(size_t i = 0, st = x + mWidth * y; i < str.length(); ++i, ++st) {
        consoleBuffer[st].Char.AsciiChar = str[i];
        consoleBuffer[st].Attributes = mCurColor;
    }
}

void ScreenConsoleBuffered::Draw(uint16_t x, uint16_t y, const std::string& str)
{
    GotoXY(x, y);
    Draw(str);
}

void ScreenConsoleBuffered::Draw(uint16_t x, uint16_t y, char str)
{
    GotoXY(x, y);
    std::string s(1, str);
    Draw(s);
}

void ScreenConsoleBuffered::Flush()
{
    SMALL_RECT consoleWriteArea = { 0, 0, mWidth - 1, mHeight - 1 };
    WriteConsoleOutputA(mOutputHandle, consoleBuffer.get(), {mWidth, mHeight}, { 0, 0 }, &consoleWriteArea);
}

#endif
