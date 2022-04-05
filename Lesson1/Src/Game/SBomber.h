#pragma once

class CollisionBridge;

class SBomber
{
public:
    SBomber();
    ~SBomber() = default;

    inline bool GetExitFlag() const
    {
        return exitFlag;
    }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    uint64_t GetPassedTime() const
    {
        return passedTime;
    }

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:
    void DeleteDynamicObj(DynamicObject* pBomb);
    void DeleteStaticObj(GameObject* pObj);

    Ground* FindGround() const;
    Plane* FindPlane() const;

    std::shared_ptr<AbstractLevelGUI> levelGUI;
    std::shared_ptr<LevelGUI1> levelGUI1;
    std::shared_ptr<LevelGUI2> levelGUI2;

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

    std::vector<std::shared_ptr<DynamicObject>> vecDynamicObj;
    std::vector<std::shared_ptr<GameObject>> vecStaticObj;

    std::unique_ptr<CollisionBridge> collisionBridge;

    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
    static const int DefaultSpeed = 4;
    static const int DefaultPosX = 5;
    static const int DefaultPosY = 10;

    friend class CollisionBridge;
};

