#pragma once

class ScreenConsoleBuffered : public IScreen, public SingletonStatic<ScreenConsoleBuffered>, public NonCopyable, public NonMoveable
{
public:
    ScreenConsoleBuffered();
    ~ScreenConsoleBuffered();

    void ClrScr() override;
    void __fastcall GotoXY(double x, double y) override;
    uint16_t GetMaxX() override;
    uint16_t GetMaxY() override;
    void SetColor(ConsoleColor color) override;
    void Draw(const std::string& str) override;
    void Flush() override;

protected:
    short mWidth{};
    short mHeight{};
    CHAR_INFO* consoleBuffer{};
    COORD mCursor{};
    ConsoleColor mCurColor{};
    HANDLE mOutputHandle{};
};

