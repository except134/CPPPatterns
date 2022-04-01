#pragma once

class ScreenConsolePlain : public IScreen, public SingletonStatic<ScreenConsolePlain>, public NonCopyable, public NonMoveable
{
public:
    void ClrScr() override;
    void GotoXY(double x, double y) override;
    uint16_t GetMaxX() override;
    uint16_t GetMaxY() override;
    void SetColor(ConsoleColor color) override;
    void Draw(const std::string& str) override;
};

