#pragma once

template<class T>
class DeleteObjectCommand : public GameCommand
{
    using ObjectsVector = std::vector<T*>;

public:
    DeleteObjectCommand(ObjectsVector& objs, T* obj) :
        object{ obj },
        objects{ objs }
    {}

    void Run() override
    {
        std::erase_if(objects, [&](const auto& i) {return i == object; });
    }

private:
    ObjectsVector& objects{};
    T* object{};
};

template<class T>
class DropBombCommand : public GameCommand
{
public:
    DropBombCommand(std::vector<DynamicObject*>& objs, const Plane* pln, uint16_t& bNumber, int16_t& scr) :
        dynamicObjects{ objs },
        plane{ pln },
        bombsNumber{ bNumber },
        score{ scr }
    {}

    void Run() override
    {
        double x = plane->GetX() + 4;
        double y = plane->GetY() + 2;

        DynamicObject* bomb = new T;
        if(!bomb) {
            return;
        }

        bomb->SetDirection(0.3, 1);
        bomb->SetSpeed(3);
        bomb->SetPos(x, y);
        bomb->SetWidth(SMALL_CRATER_SIZE);

        dynamicObjects.emplace_back(bomb);
        bombsNumber--;
        score -= Bomb::BombCost;
    }

private:
    std::vector<DynamicObject*>& dynamicObjects;
    const Plane* plane;
    uint16_t& bombsNumber;
    int16_t& score;
};

