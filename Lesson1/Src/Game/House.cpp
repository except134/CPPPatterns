// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

bool House::IsInside(double x1, double x2) const
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
    uint16_t yStart = static_cast<uint16_t>(GetY()) - GetHouseHeight();

    gScreen->SetColor(CC_Yellow);
    for(uint16_t y = 0; y < GetHouseHeight(); ++y)
        for(uint16_t x = 0; x < GetHouseWidth(); ++x)
            gScreen->Draw(static_cast<uint16_t>(GetX()) + x, yStart + y, look[y][x]);
        
}