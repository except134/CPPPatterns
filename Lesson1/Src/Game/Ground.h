#pragma once

//=============================================================================================================

enum CraterSize
{
    SMALL_CRATER_SIZE = 9
};

//=============================================================================================================

class Crater : public GameObject
{
public:
    bool IsInside(double xn) const;

    void Draw() const override;

private:

};

//=============================================================================================================

class Ground : public GameObject
{
public:
    Ground() = default;

    void Draw() const override;

    void AddCrater(double xn);

private:
    bool IsInsideAnyCrater(double x) const;

    std::vector<Crater> vecCrates;
};

