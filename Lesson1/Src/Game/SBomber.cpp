// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

SBomber::SBomber()
    : exitFlag(false),
    startTime(0),
    finishTime(0),
    deltaTime(0),
    passedTime(0),
    fps(0),
    bombsNumber(10),
    score(0)
{
    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

    std::shared_ptr<Plane> p = std::make_shared<Plane>();
    p->SetDirection(1, 0.1);
    p->SetSpeed(DefaultSpeed);
    p->SetPos(DefaultPosX, DefaultPosY);
    vecDynamicObj.emplace_back(p);


    const uint16_t maxX = gScreen->GetMaxX();
    const uint16_t maxY = gScreen->GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;

    levelGUI1 = std::make_shared<LevelGUI1>();
    levelGUI1->SetParam(passedTime, fps, bombsNumber, score);
    levelGUI1->SetPos(offset, offset);
    levelGUI1->SetWidth(width);
    levelGUI1->SetHeight(maxY - 4);
    levelGUI1->SetFinishX(offset + width - 4);

    levelGUI2 = std::make_shared<LevelGUI2>();
    levelGUI2->SetParam(passedTime, fps, bombsNumber, score);
    levelGUI2->SetPos(offset, offset);
    levelGUI2->SetWidth(width);
    levelGUI2->SetHeight(maxY - 4);
    levelGUI2->SetFinishX(offset + width - 4);

    SetGUIStrategy(levelGUI1);

    std::shared_ptr<Ground> pGr = std::make_shared<Ground>();
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    vecStaticObj.emplace_back(pGr);

    std::shared_ptr<Tank> pTank1 = std::make_shared<Tank>();
    pTank1->SetWidth(13);
    pTank1->SetPos(30, groundY - 1);
    vecStaticObj.emplace_back(pTank1);

    std::shared_ptr<Tank> pTank2 = std::make_shared<Tank>();
    pTank2->SetWidth(13);
    pTank2->SetPos(50, groundY - 1);
    vecStaticObj.emplace_back(pTank2);

    std::shared_ptr<House> pHouse = std::make_shared<House>();
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.emplace_back(pHouse);
}

void SBomber::MoveObjects()
{
    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for(size_t i = 0; i < vecDynamicObj.size(); i++) {
        if(vecDynamicObj[i] != nullptr) {
            vecDynamicObj[i]->Move(deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround<Bomb>();
    CheckBombsAndGround<BombDecorator>();
};

void SBomber::CheckPlaneAndLevelGUI()
{
    auto p = FindPlane();
    if(p) {
        if(p->GetX() > FindLevelGUI()->GetFinishX()) {
            exitFlag = true;
        }
        if(p->GetY() < 5) {
            p->SetDirection(1, 0);
            p->SetPos(p->GetX(), 5);
        }

        if(p->GetY() > gScreen->GetMaxY() - 7) {
            p->SetDirection(1, 0);
            p->SetPos(p->GetX(), gScreen->GetMaxY() - 7);
        }
    }

}

template<class T>
void SBomber::CheckBombsAndGround()
{
    vector<T*> vecBombs = FindAllBombs<T>();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for(size_t i = 0; i < vecBombs.size(); i++) {
        if(vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            DeleteDynamicObj(vecBombs[i]);
        }
    }

}

template<class T>
void SBomber::CheckDestoyableObjects(T* pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for(size_t i = 0; i < vecDestoyableObjects.size(); i++) {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if(vecDestoyableObjects[i]->IsInside(x1, x2)) {
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

void SBomber::DeleteDynamicObj(DynamicObject* pObj)
{
    CommandRunner(std::make_unique<DeleteObjectCommand<DynamicObject>>(vecDynamicObj, pObj));
}

void SBomber::DeleteStaticObj(GameObject* pObj)
{
    CommandRunner(std::make_unique<DeleteObjectCommand<GameObject>>(vecStaticObj, pObj));
}

vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for(size_t i = 0; i < vecStaticObj.size(); ++i) {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i].get());
        if(pTank != nullptr) {
            vec.emplace_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i].get());
        if(pHouse != nullptr) {
            vec.emplace_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground* SBomber::FindGround() const
{
    Ground* pGround;

    for(size_t i = 0; i < vecStaticObj.size(); ++i) {
        pGround = dynamic_cast<Ground*>(vecStaticObj[i].get());
        if(pGround != nullptr) {
            return pGround;
        }
    }

    return nullptr;
}

template<class T>
vector<T*> SBomber::FindAllBombs() const
{
    vector<T*> vecBombs;

    Iterator<T> bombs(vecDynamicObj);

    for(auto bomb : bombs) {
        vecBombs.emplace_back(bomb);
    }

    return vecBombs;
}

Plane* SBomber::FindPlane() const
{
    for(size_t i = 0; i < vecDynamicObj.size(); ++i) {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i].get());
        if(p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

AbstractLevelGUI* SBomber::FindLevelGUI() const
{
    for(size_t i = 0; i < vecStaticObj.size(); ++i) {
        AbstractLevelGUI* p = dynamic_cast<AbstractLevelGUI*>(vecStaticObj[i].get());
        if(p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if(c == 224) {
        c = _getch();
    }

    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch(c) {
        case 27: // esc
            exitFlag = true;
        break;

        case 'w':
        case 'W':
        case 72: // up
        {
            auto p = FindPlane();
            if(p) {
                p->ChangePlaneY(-0.25);
            } else {
                LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " Can't move up. Limit exceeded.");
            }
        }break;

        case 's':
        case 'S':
        case 80: // down
        {
            auto p = FindPlane();
            if(p) {
                p->ChangePlaneY(0.25);
            } else {
                LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " Can't move down. Limit exceeded.");
            }
        }break;

        case 'b':
        case 'B':
            DropBigBomb();
        break;

        case 'v':
        case 'V':
            DropSmallBomb();
        break;

        case '1':
            SetGUIStrategy(levelGUI1);
        break;

        case '2':
            SetGUIStrategy(levelGUI2);
        break;

        default:
        break;
    }
}

void SBomber::DrawFrame()
{
    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for(size_t i = 0; i < vecDynamicObj.size(); ++i) {
        if(vecDynamicObj[i] != nullptr) {
            vecDynamicObj[i]->Draw();
        }
    }

    for(size_t i = 0; i < vecStaticObj.size(); ++i) {
        if(vecStaticObj[i] != nullptr) {
            vecStaticObj[i]->Draw();
        }
    }

    gScreen->GotoXY(0, 0);
    fps++;

    auto p = FindLevelGUI();
    if(p)
        p->SetParam(passedTime, fps, bombsNumber, score);

    gScreen->Flush();
}

void SBomber::TimeStart()
{
    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

void SBomber::DropBigBomb()
{
    if(bombsNumber > 0) {
        LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

        CommandRunner(std::make_unique<DropBombCommand<BombDecorator>>(vecDynamicObj, FindPlane(), bombsNumber, score, 3));
    }
}

void SBomber::DropSmallBomb()
{
    if(bombsNumber > 0) {
        LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

        CommandRunner(std::make_unique<DropBombCommand<Bomb>>(vecDynamicObj, FindPlane(), bombsNumber, score));
    }
}

void SBomber::CommandRunner(std::unique_ptr<GameCommand> command)
{
    if(command) {
        command->Run();
    }
}

