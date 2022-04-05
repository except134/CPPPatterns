#pragma once

#ifndef _WIN32
inline bool _kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

inline int _getch()
{
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

inline uint64_t GetTickCount64()
{
    struct timespec ts;
    unsigned theTick = 0U;
    clock_gettime(CLOCK_REALTIME, &ts);
    theTick = ts.tv_nsec / 1000000;
    theTick += ts.tv_sec * 1000;
    return theTick;
}
#endif

class ScreenConsoleLinux : public IScreen, public SingletonStatic<ScreenConsoleLinux>, public NonCopyable, public NonMoveable
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

