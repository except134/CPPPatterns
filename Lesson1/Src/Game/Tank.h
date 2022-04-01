#pragma once

class Tank : public DestroyableGroundObject
{
public:
    bool IsInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override
    {
        return score;
    }

    void Draw() const override;

private:
    const uint16_t score = 30;
};
