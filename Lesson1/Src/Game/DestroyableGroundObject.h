#pragma once

class DestroyableGroundObject : public GameObject
{
public:
    virtual bool IsInside(double x1, double x2) const = 0;

    virtual inline uint16_t GetScore() const = 0;

    virtual bool HandleInsideCheck(double x1, double x2) override
    {
        return IsInside(x1, x2);
    }

    virtual DestroyableGroundObject* Clone() const = 0;
};

