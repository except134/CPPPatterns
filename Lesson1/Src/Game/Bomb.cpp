// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

void Bomb::Draw() const
{
    gScreen->SetColor(CC_LightMagenta);
    gScreen->GotoXY(x, y);
    gScreen->Draw("*");
}