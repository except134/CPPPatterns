// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

Tree::Tree(std::unique_ptr<TreeState> st) :
        state(std::move(st))
{
}

void Tree::Draw() const
{
    state->Draw(x, y);
}

void Tree::Move(uint16_t dt)
{
    time += dt * 0.001;
    if (time > growTime) {
        state->Grow(this);
        time = 0.f;
    }
}

void Tree::SetState(std::unique_ptr<TreeState> s)
{
    state = std::move(s);
}

void SmallState::Grow(Tree* tree)
{
    tree->SetState(std::make_unique<MiddleState>());
}

void SmallState::Draw(double x, double y) const
{
    gScreen->SetColor(CC_Green);
    gScreen->GotoXY(x, y - 1);
    gScreen->Draw("      *      ");
    gScreen->GotoXY(x, y);
    gScreen->Draw("     ***     ");
}

void MiddleState::Grow(Tree* tree)
{
    tree->SetState(std::make_unique<BigState>());
}

void MiddleState::Draw(double x, double y) const
{
    gScreen->SetColor(CC_Green);
    gScreen->GotoXY(x, y - 2);
    gScreen->Draw("      *      ");
    gScreen->GotoXY(x, y - 1);
    gScreen->Draw("     ***     ");
    gScreen->GotoXY(x, y);
    gScreen->Draw("    *****    ");
}

void BigState::Draw(double x, double y) const
{
    gScreen->SetColor(CC_Green);
    gScreen->GotoXY(x, y - 3);
    gScreen->Draw("      *      ");
    gScreen->GotoXY(x, y - 2);
    gScreen->Draw("     ***     ");
    gScreen->GotoXY(x, y - 1);
    gScreen->Draw("    *****    ");
    gScreen->GotoXY(x, y);
    gScreen->Draw("   *******   ");
}