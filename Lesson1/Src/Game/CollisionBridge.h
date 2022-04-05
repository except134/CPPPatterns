#pragma once

class CollisionBridge
{
public:
    CollisionBridge(SBomber* bmbr) : bomber(bmbr) {}

    void CheckPlaneAndLevelGUI();
    template<class T>
    void CheckBombsAndGround();
    template<class T>
    void CheckDestoyableObjects(T* pBomb);

private:
    SBomber* bomber;
};

#include "CollisionBridge.inl"
