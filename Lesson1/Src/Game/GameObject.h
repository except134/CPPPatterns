#pragma once

class GameObject : public Observer
{
public:
    GameObject() : x(0.0), y(0.0), width(0)
    {
    }
    virtual ~GameObject() = default;

    virtual void Draw() const = 0;

    virtual void SetPos(double nx, double ny)
    {
        x = nx; y = ny;
    }

    virtual double GetY() const
    {
        return y;
    }
    virtual double GetX() const
    {
        return x;
    }

    virtual void SetWidth(uint16_t widthN)
    {
        width = widthN;
    }
    virtual uint16_t GetWidth() const
    {
        return width;
    }

    bool HandleInsideCheck(double x1, double x2) override
    {
        return false;
    }
protected:
    double x, y;
    uint16_t width;
};