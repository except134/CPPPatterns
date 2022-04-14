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

    virtual void DrawTail() const = 0;
    virtual void DrawWing() const = 0;
    virtual void DrawBody() const = 0;
};

class ColorPlane final : public Plane
{
public:
    void DrawTail() const override;
    void DrawWing() const override;
    void DrawBody() const override;
};

class BigPlane final : public Plane
{
public:
    void DrawTail() const override;
    void DrawWing() const override;
    void DrawBody() const override;
};
