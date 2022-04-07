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
    void Draw(uint16_t x, uint16_t y, const std::string& str) override;
    void Draw(uint16_t x, uint16_t y, char str) override;
};

