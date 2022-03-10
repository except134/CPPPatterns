#pragma once

class Plane : public DynamicObject
{
public:
    void Draw() const override;

    inline void ChangePlaneY(double dy)
    {
        yDirection += dy;
    }

private:
};

