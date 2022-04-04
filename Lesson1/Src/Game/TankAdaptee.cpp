// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

void TankAdaptee::Paint() const
{
    gScreen->SetColor(CC_Red);
    gScreen->GotoXY(x, y - 3);
    gScreen->Draw("    #####");
    gScreen->GotoXY(x - 2, y - 2);
    gScreen->Draw("#######   #");
    gScreen->GotoXY(x, y - 1);
    gScreen->Draw("    #####");
    gScreen->GotoXY(x, y);
    gScreen->Draw(" ###########");

}

bool TankAdaptee::IsInRange(double x1, double x2) const
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


