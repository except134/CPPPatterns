#pragma once

class Plane : public DynamicObject
{
public:
    void Accept(const Visitor& v) override;

    void Draw() const override;

    inline void ChangePlaneY(double dy)
    {
        yDirection += dy;
    }

private:
};

