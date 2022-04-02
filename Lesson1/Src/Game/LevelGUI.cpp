// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

using namespace std;

void LevelGUI::Draw() const
{
    gScreen->SetColor(CC_White);

    gScreen->GotoXY(x, y);
    std::unique_ptr<char[]> buf = std::make_unique<char[]>(width + 1);
    if(buf == nullptr) {
        return;
    }
    std::memset(buf.get(), '+', width);
    buf[width] = '\0';
    gScreen->Draw(buf.get());
    gScreen->GotoXY(x, y + height);
    gScreen->Draw(buf.get());

    for(size_t i = size_t(y); i < height + y; i++) {
        gScreen->GotoXY(x, (double)i);
        gScreen->Draw("+");
        gScreen->GotoXY(x + width - 1, (double)i);
        gScreen->Draw("+");
    }

    {
        std::stringstream s;
        gScreen->GotoXY(3, 1);
        int fpss = static_cast<int>(fps / (passedTime / 1000.0));
        s << "FramePerSecond: " << (fpss > 0 ? fpss : 0);
        gScreen->Draw(s.str());
    }
    {
        std::stringstream s;
        gScreen->GotoXY(25, 1);
        s << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
        gScreen->Draw(s.str());
    }
    {
        std::stringstream s;
        gScreen->GotoXY(46, 1);
        s << "BombsNum: " << bombsNumber;
        gScreen->Draw(s.str());
    }
    {
        std::stringstream s;
        gScreen->GotoXY(62, 1);
        s << "Score: " << score;
        gScreen->Draw(s.str());
    }

}

void LevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew)
{
    passedTime = passedTimeNew;
    fps = fpsNew;
    bombsNumber = bombsNumberNew;
    score = scoreNew;
}
