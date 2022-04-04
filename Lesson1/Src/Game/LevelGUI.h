#pragma once

class AbstractLevelGUI : public GameObject
{
public:
    virtual void SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew)    
    {
        passedTime = passedTimeNew;
        fps = fpsNew;
        bombsNumber = bombsNumberNew;
        score = scoreNew;
    }

    virtual void SetHeight(uint16_t heightN)
    {
        height = heightN;
    }

    virtual uint16_t GetFinishX() const
    {
        return finishX;
    }

    virtual void SetFinishX(uint16_t finishXN)
    {
        finishX = finishXN;
    }

protected:
    uint16_t height{ 0 };
    uint16_t finishX{ 109 };

    uint64_t passedTime{ 0 };
    uint64_t fps{ 0 };
    uint16_t bombsNumber{ 0 };
    int16_t score{ 0 };
};

class LevelGUI1 : public AbstractLevelGUI
{
public:
    void Draw() const override;
};

class LevelGUI2 : public AbstractLevelGUI
{
public:
    void Draw() const override;
};



