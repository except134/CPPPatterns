// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

bool House::isInside(double x1, double x2) const
{
    const double XBeg = x + 2;
    const double XEnd = x + width - 1;

    if(x1 < XBeg && x2 > XEnd) {
        return true;
    }

    if(x1 > XBeg && x1 < XEnd) {
        return true;
    }

    if(x2 > XBeg && x2 < XEnd) {
        return true;
    }

    return false;
}

void House::Draw() const
{
    gScreen->SetColor(CC_Yellow);
    gScreen->GotoXY(x, y - 5);
    gScreen->Draw("  ########  ");
    gScreen->GotoXY(x, y - 4);
    gScreen->Draw("##        ##");
    gScreen->GotoXY(x, y - 3);
    gScreen->Draw("############");
    gScreen->GotoXY(x, y - 2);
    gScreen->Draw("#          #");
    gScreen->GotoXY(x, y - 1);
    gScreen->Draw("#          #");
    gScreen->GotoXY(x, y);
    gScreen->Draw("############");
}