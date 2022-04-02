#pragma once

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
    void CheckPlaneAndLevelGUI();
    template<class T>
    void CheckBombsAndGround();
    template<class T>
    void CheckDestoyableObjects(T* pBomb);

    void DeleteDynamicObj(DynamicObject* pBomb);
    void DeleteStaticObj(GameObject* pObj);

    Ground* FindGround() const;
    Plane* FindPlane() const;
    LevelGUI* FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    template<class T>
    std::vector<T*> FindAllBombs() const;

    void DropBigBomb();
    void DropSmallBomb();

    std::vector<std::shared_ptr<DynamicObject>> vecDynamicObj;
    std::vector<std::shared_ptr<GameObject>> vecStaticObj;

    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
    static const int DefaultSpeed = 4;
    static const int DefaultPosX = 5;
    static const int DefaultPosY = 10;
};

