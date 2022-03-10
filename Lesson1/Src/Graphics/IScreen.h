#pragma once

// Палитра цветов от 0 до 15
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

class IScreen
{
public:
    virtual void ClrScr() = 0;
    virtual void __fastcall GotoXY(double x, double y) = 0;
    virtual uint16_t GetMaxX() = 0;
    virtual uint16_t GetMaxY() = 0;
    virtual void SetColor(ConsoleColor color) = 0;
    virtual void Draw(const std::string& str) = 0;
    virtual void Flush() {};
};

inline IScreen* gScreen;
