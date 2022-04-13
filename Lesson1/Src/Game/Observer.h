#pragma once

class Observer
{
public:
    virtual ~Observer() = default;
    virtual bool HandleInsideCheck(double x1, double x2) = 0;
};


