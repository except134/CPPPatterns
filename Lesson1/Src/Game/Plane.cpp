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
    DrawTail();
    DrawWing();
    DrawBody();

/*
    gScreen->SetColor(CC_LightBlue);
    gScreen->GotoXY(x, y);
    gScreen->Draw("=========>");
    gScreen->GotoXY(x - 2, y - 1);
    gScreen->Draw("===");
    gScreen->GotoXY(x + 3, y - 1);
    gScreen->Draw("\\\\\\\\");
    gScreen->GotoXY(x + 3, y + 1);
    gScreen->Draw("////");
*/
}

void ColorPlane::DrawTail() const
{
    gScreen->SetColor(CC_LightBlue);
    gScreen->GotoXY(x - 2, y - 1);
    gScreen->Draw("===");
}

void ColorPlane::DrawWing() const
{
    gScreen->SetColor(CC_LightGreen);
    gScreen->GotoXY(x + 3, y - 1);
    gScreen->Draw("\\\\\\\\");
    gScreen->GotoXY(x + 3, y + 1);
    gScreen->Draw("////");
}

void ColorPlane::DrawBody() const
{
    gScreen->SetColor(CC_LightMagenta);
    gScreen->GotoXY(x, y);
    gScreen->Draw("=========>");
}

void BigPlane::DrawTail() const
{
    gScreen->SetColor(CC_LightBlue);
    gScreen->GotoXY(x - 2, y - 1);
    gScreen->Draw("===");
}

void BigPlane::DrawWing() const
{
    gScreen->SetColor(CC_LightBlue);
    gScreen->GotoXY(x + 3, y - 1);
    gScreen->Draw("\\\\\\\\");
    gScreen->GotoXY(x + 3, y + 1);
    gScreen->Draw("////");
}

void BigPlane::DrawBody() const
{
    gScreen->SetColor(CC_LightBlue);
    gScreen->GotoXY(x, y);
    gScreen->Draw("=========>");
}
