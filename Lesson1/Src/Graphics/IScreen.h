#pragma once

// Палитра цветов от 0 до 15
#ifdef _WIN32
enum ConsoleColor
{
    CC_Black = 0,
    CC_Blue,
    CC_Green,
    CC_Cyan,
    CC_Red,
    CC_Magenta,
    CC_Brown,
    CC_LightGray,
    CC_DarkGray,
    CC_LightBlue,
    CC_LightGreen,
    CC_LightCyan,
    CC_LightRed,
    CC_LightMagenta,
    CC_Yellow,
    CC_White
};
#else
enum ConsoleColor
{
    CC_Black = 30,
    CC_Blue = 34,
    CC_Green = 32,
    CC_Cyan = 36,
    CC_Red = 31,
    CC_Magenta = 35,
    CC_Brown = 33,
    CC_LightGray = 37,
    CC_DarkGray = 100,
    CC_LightBlue = 94,
    CC_LightGreen = 92,
    CC_LightCyan = 96,
    CC_LightRed = 91,
    CC_LightMagenta = 95,
    CC_Yellow = 93,
    CC_White = 97
};
#endif

class IScreen
{
public:
    virtual void ClrScr() = 0;
    virtual void GotoXY(double x, double y) = 0;
    virtual uint16_t GetMaxX() = 0;
    virtual uint16_t GetMaxY() = 0;
    virtual void SetColor(ConsoleColor color) = 0;
    virtual void Draw(const std::string& str) = 0;
    virtual void Flush() {};
};

inline IScreen* gScreen;
