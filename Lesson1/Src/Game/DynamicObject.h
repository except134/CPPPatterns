#pragma once

class DynamicObject : public GameObject 
{
public:
    DynamicObject() : speed(0.0), xDirection(0.0), yDirection(0) { }

    virtual void SetSpeed(double sp) { speed = sp; }
    virtual double GetSpeed() const { return speed; }

    virtual void SetDirection(double dx, double dy) { xDirection = dx; yDirection = dy; }
    virtual std::tuple<double, double> GetDirection() const { return std::tie(xDirection, yDirection); }

    virtual void Move(uint16_t time) { x += xDirection * speed * time * 0.001; y += yDirection * speed * time * 0.001; }

    virtual void Accept(const Visitor& v) {}

protected:
    double speed;
    double xDirection, yDirection;
};