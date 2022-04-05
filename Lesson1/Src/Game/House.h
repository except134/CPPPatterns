#pragma once

constexpr size_t HouseWidth = 14;
constexpr size_t HouseHeight = 7;

class House : public DestroyableGroundObject
{
public:
    bool IsInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override
    {
        return score;
    }

    void Draw() const override;

    constexpr size_t GetHouseWidth() const { return HouseWidth; }
    constexpr size_t GetHouseHeight() const { return HouseHeight; }

private:
    friend class HouseBuilderA;
    friend class HouseBuilderB;
    friend class HouseBuilderC;

    const uint16_t score = 40;

    char look[HouseHeight][HouseWidth]{};
};

