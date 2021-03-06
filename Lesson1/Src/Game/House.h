#pragma once

constexpr uint16_t HouseWidth = 14;
constexpr uint16_t HouseHeight = 7;

class House : public DestroyableGroundObject
{
public:
    House() = default;

    bool IsInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override
    {
        return score;
    }

    void Draw() const override;

    House* Clone() const override
    {
        return new House(*this);
    }

    constexpr uint16_t GetHouseWidth() const { return HouseWidth; }
    constexpr uint16_t GetHouseHeight() const { return HouseHeight; }

private:
    friend class HouseBuilderA;
    friend class HouseBuilderB;
    friend class HouseBuilderC;

    House(const House& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        width = rhs.width;
    }

    const uint16_t score = 40;

    char look[HouseHeight][HouseWidth]{};
};

