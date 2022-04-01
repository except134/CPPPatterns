#pragma once

class SBomber
{
public:
    SBomber();
    ~SBomber();

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
    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void CheckDestoyableObjects(BombDecorator* pBomb);

    void DeleteDynamicObj(DynamicObject* pBomb);
    void DeleteStaticObj(GameObject* pObj);

    Ground* FindGround() const;
    Plane* FindPlane() const;
    LevelGUI* FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<BombDecorator*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;

    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
    static const int DefaultSpeed = 4;
    static const int DefaultPosX = 5;
    static const int DefaultPosY = 10;
};
