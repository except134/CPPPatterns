// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

std::vector<std::string> Tank::messages{
    "!!!",
    "***",
    "Asshole",
    "I kill you!!!"
};

void Tank::SendMessage() const
{
    if(!messages.empty()) {
        std::random_device rd;
        std::mt19937 rdnum(rd());
        uint64_t index{ rdnum() % messages.size() };
        auto iter = messages.begin() + index;
        std::unique_ptr<TankMessage> msg = std::make_unique<TankMessage>(x, y, messages.at(index));
        mediator.get()->SendMessage(std::move(msg));
        messages.erase(iter);
    }
}

bool Tank::IsInside(double x1, double x2) const
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

void Tank::Draw() const
{
    gScreen->SetColor(CC_Brown);
    gScreen->GotoXY(x, y - 3);
    gScreen->Draw("    #####");
    gScreen->GotoXY(x - 2, y - 2);
    gScreen->Draw("#######   #");
    gScreen->GotoXY(x, y - 1);
    gScreen->Draw("    #####");
    gScreen->GotoXY(x, y);
    gScreen->Draw(" ###########");

    SendMessage();
}

