// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

void Bomb::Accept(const Visitor& v)
{
    v.Log(*this);
}

void BombDecorator::Accept(const Visitor& v)
{
    v.Log(*this);
}

void Bomb::Draw() const
{
    gScreen->SetColor(CC_LightMagenta);
    gScreen->GotoXY(x, y);
    gScreen->Draw("*");
}

void BombDecorator::Draw() const
{
    bomb.Draw();
    gScreen->GotoXY(bomb.GetX() + 1, bomb.GetY());
    gScreen->Draw("*");
    gScreen->GotoXY(bomb.GetX() - 1, bomb.GetY());
    gScreen->Draw("*");
    gScreen->GotoXY(bomb.GetX(), bomb.GetY() + 1);
    gScreen->Draw("*");
    gScreen->GotoXY(bomb.GetX(), bomb.GetY() - 1);
    gScreen->Draw("V");
}

void BombDecorator::Move(uint16_t time) 
{
    bomb.Move(time);
}

void BombDecorator::SetPos(double nx, double ny)
{
    bomb.SetPos(nx, ny);
}

double BombDecorator::GetY() const
{
    return bomb.GetY();
}

double BombDecorator::GetX() const
{
    return bomb.GetX();
}

void BombDecorator::SetWidth(uint16_t widthN)
{
    bomb.SetWidth(widthN);
}

uint16_t BombDecorator::GetWidth() const
{
    return bomb.GetWidth();
}

void BombDecorator::SetSpeed(double sp)
{
    bomb.SetSpeed(sp);
}

double BombDecorator::GetSpeed() const
{
    return bomb.GetSpeed();
}

void BombDecorator::SetDirection(double dx, double dy)
{
    bomb.SetDirection(dx, dy);
}

std::tuple<double, double> BombDecorator::GetDirection() const
{
    return bomb.GetDirection();
}

