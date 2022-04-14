// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

inline void CollisionBridge::CheckPlaneAndLevelGUI()
{
    auto p = bomber->FindPlane();
    if(p) {
        if(p->GetX() > bomber->FindLevelGUI()->GetFinishX()) {
            bomber->SetExitFlag(true);
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
inline void CollisionBridge::CheckBombsAndGround()
{
    std::vector<T*> vecBombs = bomber->FindAllBombs<T>();
    Ground* pGround = bomber->FindGround();
    const double y = pGround->GetY();
    for(size_t i = 0; i < vecBombs.size(); i++) {
        if(vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            bomber->DeleteDynamicObj(vecBombs[i]);
        }
    }

}

template<class T>
inline void CollisionBridge::CheckDestoyableObjects(T* pBomb)
{
    std::vector<DestroyableGroundObject*> vecDestoyableObjects = bomber->FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for(size_t i = 0; i < vecDestoyableObjects.size(); i++) {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if(vecDestoyableObjects[i]->IsInside(x1, x2)) {
            bomber->AddScore(vecDestoyableObjects[i]->GetScore());
            bomber->DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

