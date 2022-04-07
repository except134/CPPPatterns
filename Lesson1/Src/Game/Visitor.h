#pragma once

class Plane;
class Bomb;
class BombDecorator;

class Visitor
{
public:
    ~Visitor() = default;

    virtual void Log(const Plane& p) const = 0;
    virtual void Log(const Bomb& p) const = 0;
    virtual void Log(const BombDecorator& p) const = 0;
};

class LogVisitor : public Visitor
{
public:
    void Log(const Plane& p) const override;
    void Log(const Bomb& p) const override;
    void Log(const BombDecorator& p) const override;
};



