// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

class SBomber::SBomberImpl
{
public:
    SBomberImpl();
    ~SBomberImpl() = default;
        
    void DeleteDynamicObj(DynamicObject* pBomb);
    void DeleteStaticObj(GameObject* pObj);

    Ground* FindGround() const;
    Plane* FindPlane() const;

    void SetGUIStrategy(std::shared_ptr<AbstractLevelGUI> g)
    {
        std::erase_if(vecStaticObj, [&](const auto& i) { return i.get() == levelGUI.get(); });
        levelGUI = g;
        vecStaticObj.emplace_back(levelGUI);
    }

    AbstractLevelGUI* FindLevelGUI() const;

    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    template<class T>
    std::vector<T*> FindAllBombs() const;

    void DropBigBomb();
    void DropSmallBomb();

    void CommandRunner(std::unique_ptr<GameCommand> command);

public:
    std::shared_ptr<AbstractLevelGUI> levelGUI;
    std::shared_ptr<LevelGUI1> levelGUI1;
    std::shared_ptr<LevelGUI2> levelGUI2;
    std::vector<std::shared_ptr<DynamicObject>> vecDynamicObj;
    std::vector<std::shared_ptr<GameObject>> vecStaticObj;

    std::unique_ptr<CollisionBridge> collisionBridge;
    LogVisitor logVisitor;
    std::shared_ptr<Mediator> mediator;

    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
    static const int DefaultSpeed = 4;
    static const int DefaultPosX = 5;
    static const int DefaultPosY = 10;

    friend class CollisionBridge;
};

SBomber::SBomberImpl::SBomberImpl()
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

    std::shared_ptr<Plane> p;

    if(rand() % 20 < 10) {
        p = std::make_shared<ColorPlane>();
    } else {
        p = std::make_shared<BigPlane>();
    }

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

    uint16_t tankWidth = 13;
    uint16_t tankSpace = 10;
    uint16_t tankStartX = ((width - 2) - (tankWidth + tankSpace) * 4) / 2;

    mediator = std::make_shared<Mediator>();
    mediator->Add(levelGUI);

    std::shared_ptr<Tree> pTree = std::make_shared<Tree>(std::make_unique<SmallState>());
    pTree->SetWidth(tankWidth);
    pTree->SetPos(tankStartX, groundY - 1);
    vecDynamicObj.emplace_back(pTree);

    std::shared_ptr<TankAdapter> pTankAdaptee = std::make_shared<TankAdapter>();
    pTankAdaptee->SetWidth(tankWidth);
    pTankAdaptee->SetPos(pTree->GetX() + tankWidth + tankSpace, groundY - 1);
    vecStaticObj.emplace_back(pTankAdaptee);

    std::shared_ptr<Tank> pTank1 = std::make_shared<Tank>(mediator);
    pTank1->SetWidth(tankWidth);
    pTank1->SetPos(pTankAdaptee->GetX() + tankWidth + tankSpace, groundY - 1);
    vecStaticObj.emplace_back(pTank1);

    std::shared_ptr<Tank> pTank2 = std::make_shared<Tank>(mediator);
    pTank2->SetWidth(tankWidth);
    pTank2->SetPos(pTank1->GetX() + tankWidth + tankSpace, groundY - 1);
    vecStaticObj.emplace_back(pTank2);

    HouseDirector houseDirector;
    HouseBuilderA houseBuilderA;
    HouseBuilderB houseBuilderB;
    HouseBuilderC houseBuilderC;

    std::shared_ptr<House> pHouse;

    std::cout << "\tChoose house type:\n";
    std::cout << "\t1: Floor, Walls, Roof, Pipe\n";
    std::cout << "\t2: Floor, Walls, Windows, Roof\n";
    std::cout << "\t3: All elements\n";

    int houseType{ 0 };
    while(houseType < 1 || houseType > 3)
        std::cin >> houseType;

    switch(houseType) {
        case 1:
        pHouse = houseDirector.CreateHouse(houseBuilderA);
        break;
        case 2:
        pHouse = houseDirector.CreateHouse(houseBuilderB);
        break;
        case 3:
        pHouse = houseDirector.CreateHouse(houseBuilderC);
        break;
        default:
        break;
    }
    pHouse->SetPos(pTank2->GetX() + tankWidth + tankSpace, groundY);
    vecStaticObj.emplace_back(pHouse);

}

SBomber::SBomber()
{
    pImpl = new SBomberImpl();
    pImpl->collisionBridge = std::make_unique<CollisionBridge>(this);
}

SBomber::~SBomber()
{
    delete pImpl;
}

Ground* SBomber::FindGround() const
{
    return pImpl->FindGround();
}

AbstractLevelGUI* SBomber::FindLevelGUI() const
{
    return pImpl->FindLevelGUI();
}

Plane* SBomber::FindPlane() const
{
    return pImpl->FindPlane();
}

template<class T>
std::vector<T*> SBomber::FindAllBombs() const
{
    return pImpl->FindAllBombs<T>();
}

void SBomber::DeleteDynamicObj(DynamicObject* pBomb)
{
    pImpl->DeleteDynamicObj(pBomb);
}

void SBomber::DeleteStaticObj(GameObject* pObj)
{
    pImpl->DeleteStaticObj(pObj);
}

std::vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
{
    return pImpl->FindDestoyableGroundObjects();
}

void SBomber::AddScore(uint16_t score)
{
    pImpl->score += score;
}

bool SBomber::GetExitFlag() const
{
    return pImpl->exitFlag;
}

void SBomber::SetExitFlag(bool val)
{
    pImpl->exitFlag = val;
}

uint64_t SBomber::GetPassedTime() const
{
    return pImpl->passedTime;
}

void SBomber::MoveObjects()
{
    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for(size_t i = 0; i < pImpl->vecDynamicObj.size(); i++) {
        if(pImpl->vecDynamicObj[i] != nullptr) {
            pImpl->vecDynamicObj[i]->Move(pImpl->deltaTime);
            pImpl->vecDynamicObj[i]->Accept(pImpl->logVisitor);
        }
    }
};

void SBomber::CheckObjects()
{
    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

    pImpl->collisionBridge->CheckPlaneAndLevelGUI();
    pImpl->collisionBridge->CheckBombsAndGround<Bomb>();
    pImpl->collisionBridge->CheckBombsAndGround<BombDecorator>();
};

void SBomber::SBomberImpl::DeleteDynamicObj(DynamicObject* pObj)
{
    CommandRunner(std::make_unique<DeleteObjectCommand<DynamicObject>>(vecDynamicObj, pObj));
}

void SBomber::SBomberImpl::DeleteStaticObj(GameObject* pObj)
{
    CommandRunner(std::make_unique<DeleteObjectCommand<GameObject>>(vecStaticObj, pObj));
}

vector<DestroyableGroundObject*> SBomber::SBomberImpl::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    TankAdapter* pTankAdapter;
    House* pHouse;
    for(size_t i = 0; i < vecStaticObj.size(); ++i) {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i].get());
        if(pTank != nullptr) {
            vec.emplace_back(pTank);
            continue;
        }

        pTankAdapter = dynamic_cast<TankAdapter*>(vecStaticObj[i].get());
        if(pTankAdapter != nullptr) {
            vec.emplace_back(pTankAdapter);
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

Ground* SBomber::SBomberImpl::FindGround() const
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
vector<T*> SBomber::SBomberImpl::FindAllBombs() const
{
    vector<T*> vecBombs;

    Iterator<T> bombs(vecDynamicObj);

    for(auto bomb : bombs) {
        vecBombs.emplace_back(bomb);
    }

    return vecBombs;
}

Plane* SBomber::SBomberImpl::FindPlane() const
{
    for(size_t i = 0; i < vecDynamicObj.size(); ++i) {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i].get());
        if(p != nullptr) {
            return p;
        }
    }

    return nullptr;
}

AbstractLevelGUI* SBomber::SBomberImpl::FindLevelGUI() const
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
            pImpl->exitFlag = true;
        break;

        case 'w':
        case 'W':
        case 72: // up
        {
            auto p = pImpl->FindPlane();
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
            auto p = pImpl->FindPlane();
            if(p) {
                p->ChangePlaneY(0.25);
            } else {
                LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " Can't move down. Limit exceeded.");
            }
        }break;

        case 'b':
        case 'B':
            pImpl->DropBigBomb();
        break;

        case 'v':
        case 'V':
            pImpl->DropSmallBomb();
        break;

        case '1':
            pImpl->SetGUIStrategy(pImpl->levelGUI1);
        break;

        case '2':
            pImpl->SetGUIStrategy(pImpl->levelGUI2);
        break;

        default:
        break;
    }
}

void SBomber::DrawFrame()
{
    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for(size_t i = 0; i < pImpl->vecDynamicObj.size(); ++i) {
        if(pImpl->vecDynamicObj[i] != nullptr) {
            pImpl->vecDynamicObj[i]->Draw();
        }
    }

    for(size_t i = 0; i < pImpl->vecStaticObj.size(); ++i) {
        if(pImpl->vecStaticObj[i] != nullptr) {
            pImpl->vecStaticObj[i]->Draw();
        }
    }

    gScreen->GotoXY(0, 0);
    pImpl->fps++;

    auto p = pImpl->FindLevelGUI();
    if(p) {
        p->SetParam(pImpl->passedTime, pImpl->fps, pImpl->bombsNumber, pImpl->score);
        p->ChangeMessage();
    }

    gScreen->Flush();
}

void SBomber::TimeStart()
{
    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");
    pImpl->startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    pImpl->finishTime = GetTickCount64();
    pImpl->deltaTime = uint16_t(pImpl->finishTime - pImpl->startTime);
    pImpl->passedTime += pImpl->deltaTime;

    LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)pImpl->deltaTime);
}

void SBomber::SBomberImpl::DropBigBomb()
{
    if(bombsNumber > 0) {
        LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

        CommandRunner(std::make_unique<DropBombCommand<BombDecorator>>(vecDynamicObj, FindPlane(), bombsNumber, score, 3));
    }
}

void SBomber::SBomberImpl::DropSmallBomb()
{
    if(bombsNumber > 0) {
        LoggerProxy::Instance().WriteToLog(string(__FUNCTION__) + " was invoked");

        CommandRunner(std::make_unique<DropBombCommand<Bomb>>(vecDynamicObj, FindPlane(), bombsNumber, score));
    }
}

void SBomber::SBomberImpl::CommandRunner(std::unique_ptr<GameCommand> command)
{
    if(command) {
        command->Run();
    }
}

