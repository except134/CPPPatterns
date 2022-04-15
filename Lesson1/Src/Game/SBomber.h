#pragma once

class CollisionBridge;

class SBomber : public NonCopyable, NonMoveable
{
public:
    SBomber();
    ~SBomber();

    bool GetExitFlag() const;
    void SetExitFlag(bool val);

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();
    uint64_t GetPassedTime() const;

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

    // Для паттерна Мост
    Ground* FindGround() const;
    AbstractLevelGUI* FindLevelGUI() const;
    Plane* FindPlane() const;
    template<class T>
    std::vector<T*> FindAllBombs() const;
    void DeleteDynamicObj(DynamicObject* pBomb);
    void DeleteStaticObj(GameObject* pObj);
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    void AddScore(uint16_t score);

private:
    class SBomberImpl;
    SBomberImpl* pImpl;
};

