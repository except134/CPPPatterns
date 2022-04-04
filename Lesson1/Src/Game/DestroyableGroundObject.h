#pragma once

class DestroyableGroundObject : public GameObject
{
public:
    virtual bool IsInside(double x1, double x2) const = 0;

    virtual inline uint16_t GetScore() const = 0;

protected:

};