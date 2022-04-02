// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

//==================================================================================================

void Crater::Draw() const
{
    if(width == SMALL_CRATER_SIZE) // Рисование воронки в 9 символов шириной
    {
        gScreen->GotoXY(x - 4, y + 1);
        gScreen->Draw("==     ==");
        gScreen->GotoXY(x - 2, y + 2);
        gScreen->Draw("=====");
    }
}

bool Crater::IsInside(double xn) const
{
    const double size_2 = width / 2.0;

    if(int(xn) > int(x - size_2) && xn <= int(x + size_2)) {
        return true;
    }

    return false;
}

//==================================================================================================

void Ground::Draw() const
{
    gScreen->SetColor(CC_Green);

    const size_t bufSize = width + 1;
    char* buf = new (nothrow) char[bufSize];
    if(buf == nullptr) {
        return;
    }

    if(vecCrates.size() == 0) {
        gScreen->GotoXY(x, y);
        memset(buf, '=', bufSize);
        buf[bufSize - 1] = '\0';
        gScreen->Draw(buf);
    } else {
        const size_t X = size_t(x);
        char c;
        for(size_t i = X; i < width + X; i++) {
            c = (IsInsideAnyCrater((double)i)) ? ' ' : '=';
            buf[i - X] = c;
        }

        gScreen->GotoXY((double)X, y);
        buf[bufSize - 1] = '\0';
        gScreen->Draw(buf);

        for(size_t i = 0; i < vecCrates.size(); i++) {
            vecCrates[i].Draw();
        }
    }

    delete[] buf;
}

bool Ground::IsInsideAnyCrater(double valX) const
{
    bool isInside = false;
    for(size_t i = 0; i < vecCrates.size(); i++) {
        if(vecCrates[i].IsInside(valX)) {
            isInside = true;
            break;
        }
    }

    return isInside;
}

void Ground::AddCrater(double xn)
{
    Crater cr;
    cr.SetPos(int(xn), y);
    cr.SetWidth(SMALL_CRATER_SIZE);
    vecCrates.push_back(cr);
}
