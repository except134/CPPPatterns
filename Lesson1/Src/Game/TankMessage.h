#pragma once

struct TankMessage
{
    double x{}, y{};
    std::string text{};
    TankMessage() = default;
    virtual ~TankMessage() = default;
    TankMessage(double xx, double yy, std::string txt) : x(xx), y(yy), text(txt)
    {
    }
};

