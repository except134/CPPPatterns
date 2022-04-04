#pragma once

template<class T>
class DeleteObjectCommand : public GameCommand
{
    using ObjectsVector = std::vector<std::shared_ptr<T>>;

public:
    DeleteObjectCommand(ObjectsVector& objs, T* obj) :
        object{ obj },
        objects{ objs }
    {}

    void Run() override
    {
        std::erase_if(objects, [&](const auto& i) {return i.get() == object; });
    }

private:
    ObjectsVector& objects{};
    T* object{};
};

template<class T>
class DropBombCommand : public GameCommand
{
    using ObjectsVector = std::vector<std::shared_ptr<DynamicObject>>;

public:
    DropBombCommand(ObjectsVector& objs, const Plane* pln, uint16_t& bNumber, int16_t& scr, double sp = 2.0, CraterSize craterSz = SMALL_CRATER_SIZE) :
        dynamicObjects{ objs },
        plane{ pln },
        bombsNumber{ bNumber },
        score{ scr },
        speed{ sp },
        craterSize{ craterSz }
    {}

    void Run() override
    {
        double x = plane->GetX() + 4;
        double y = plane->GetY() + 2;

        std::shared_ptr<DynamicObject> bomb = std::make_shared<T>();
        if(!bomb) {
            return;
        }

        bomb->SetDirection(0.3, 1);
        bomb->SetSpeed(speed);
        bomb->SetPos(x, y);
        bomb->SetWidth(craterSize);

        dynamicObjects.emplace_back(bomb);
        bombsNumber--;
        score -= T::BombCost;
    }

private:
    ObjectsVector& dynamicObjects;
    const Plane* plane;
    uint16_t& bombsNumber;
    int16_t& score;
    double speed{};
    CraterSize craterSize{};
};

