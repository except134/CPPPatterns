#pragma once

using DestroyableObject = std::shared_ptr<DestroyableGroundObject>;
using DestroyableObjectsVector = std::vector<DestroyableObject>;

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

    virtual DestroyableObjectsVector CheckDestroyableObjects(uint16_t& score)
    {
        DestroyableObjectsVector ret;
        
        const double size = GetWidth();
        const double sizeHalf = size / 2;
        
        for(auto& obsrv : observers) {
            const double x1 = GetX() - sizeHalf;
            const double x2 = x1 + size;

            if(obsrv->HandleInsideCheck(x1, x2)) {
                score += obsrv->GetScore();
                ret.emplace_back(obsrv);
            }
        }

        return ret;
    }

    void AddObserver(DestroyableObject obsrv)
    {
        if(obsrv) {
            observers.emplace_back(obsrv);
        }
    }

    void AddObservers(DestroyableObjectsVector& obsrvs)
    {
        for(auto& i : obsrvs)
            AddObserver(i);
    }

    void DelObserver(const DestroyableObject& obsrv)
    {
        std::erase_if(observers, [&](const auto& i) {return i.get() == obsrv.get(); });
    }

protected:
    double speed;
    double xDirection, yDirection;
    DestroyableObjectsVector observers;
};

