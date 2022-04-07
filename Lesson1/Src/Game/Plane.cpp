// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

void Plane::Accept(const Visitor& v)
{
    v.Log(*this);
}

void Plane::Draw() const
{
    gScreen->SetColor(CC_LightBlue);
    gScreen->GotoXY(x, y);
    gScreen->Draw("=========>");
    gScreen->GotoXY(x - 2, y - 1);
    gScreen->Draw("===");
    gScreen->GotoXY(x + 3, y - 1);
    gScreen->Draw("\\\\\\\\");
    gScreen->GotoXY(x + 3, y + 1);
    gScreen->Draw("////");
}
