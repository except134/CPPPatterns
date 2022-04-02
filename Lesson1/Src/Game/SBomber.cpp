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

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(DefaultSpeed);
    p->SetPos(DefaultPosX, DefaultPosY);
    vecDynamicObj.push_back(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = gScreen->GetMaxX();
    const uint16_t maxY = gScreen->GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    vecStaticObj.push_back(pGr);

    Tank* pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    vecStaticObj.push_back(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    vecStaticObj.push_back(pTank);

    House* pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);
}

SBomber::~SBomber()
{
    for(size_t i = 0; i < vecDynamicObj.size(); i++) {
        delete vecDynamicObj[i];
    }

    for(size_t i = 0; i < vecStaticObj.size(); i++) {
        delete vecStaticObj[i];
    }
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
    std::unique_ptr<GameCommand> command = std::make_unique<DeleteObjectCommand<DynamicObject>>(vecDynamicObj, pObj);
    command->Run();
}

void SBomber::DeleteStaticObj(GameObject* pObj)
{
    std::unique_ptr<GameCommand> command = std::make_unique<DeleteObjectCommand<GameObject>>(vecStaticObj, pObj);
    command->Run();
}

vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for(size_t i = 0; i < vecStaticObj.size(); ++i) {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if(pTank != nullptr) {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if(pHouse != nullptr) {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground* SBomber::FindGround() const
{
    Ground* pGround;

    for(size_t i = 0; i < vecStaticObj.size(); ++i) {
        pGround = dynamic_cast<Ground*>(vecStaticObj[i]);
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

    for(size_t i = 0; i < vecDynamicObj.size(); ++i) {
        T* pBomb = dynamic_cast<T*>(vecDynamicObj[i]);
        if(pBomb != nullptr) {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

Plane* SBomber::FindPlane() const
{
    for(size_t i = 0; i < vecDynamicObj.size(); ++i) {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if(p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* SBomber::FindLevelGUI() const
{
    for(size_t i = 0; i < vecStaticObj.size(); ++i) {
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
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

        std::unique_ptr<GameCommand> command = std::make_unique<DropBombCommand<BombDecorator>>(vecDynamicObj, FindPlane(), bombsNumber, score);
        command->Run();
    }
}

void SBomber::DropSmallBomb()
{
    if(bombsNumber > 0) {
        LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

        std::unique_ptr<GameCommand> command = std::make_unique<DropBombCommand<Bomb>>(vecDynamicObj, FindPlane(), bombsNumber, score);
        command->Run();
    }
}
