#pragma once

class Bomb : public DynamicObject
{
public:
    static const uint16_t BombCost = 5; 

    void Accept(const Visitor& v) override;

    void Draw() const override;
};

class BombDecorator : public DynamicObject
{
public:
    static const uint16_t BombCost = 10;

    void Accept(const Visitor& v) override;

    void Draw() const override;
    void Move(uint16_t time) override;
    void SetPos(double nx, double ny) override;
    double GetY() const override;
    double GetX() const override;
    void SetWidth(uint16_t width) override;
    uint16_t GetWidth() const override;
    void SetSpeed(double sp) override;
    double GetSpeed() const override;
    void SetDirection(double dx, double dy) override;
    std::tuple<double, double> GetDirection() const override;

private:
    Bomb bomb;
};
