#pragma once

class TankAdapter : public DestroyableGroundObject
{
public:
    void SetPos(double nx, double ny) override
    {
        tank.SetPos(nx, ny);
    }

    double GetY() const override
    {
        return tank.GetY();
    }

    double GetX() const override
    {
        return tank.GetX();
    }

    void SetWidth(uint16_t widthN) override
    {
        tank.SetWidth(widthN);
    }

    uint16_t GetWidth() const override
    {
        return tank.GetWidth();
    }

    void Draw() const override
    {
        tank.Paint();
    }

    bool IsInside(double x1, double x2) const override
    {
        return tank.IsInRange(x1, x2);
    }

    inline uint16_t GetScore() const override
    {
        return tank.GetScore();
    }

private:
    TankAdaptee tank;
};

