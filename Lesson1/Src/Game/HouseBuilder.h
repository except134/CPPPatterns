#pragma once

class HouseBuilder
{
public:
    HouseBuilder() = default;
    virtual ~HouseBuilder() = default;

    void CreateHouse()
    {
        house = std::make_shared<House>();
    }

    virtual std::shared_ptr<House> GetHouse()
    {
        return house;
    }

    virtual void BuildFloor(){}
    virtual void BuildWalls(){}
    virtual void BuildWindows(){}
    virtual void BuildDoor(){}
    virtual void BuildRoof(){}
    virtual void BuildPipe(){}

protected:
    std::shared_ptr<House> house;
};

class HouseBuilderA : public HouseBuilder
{
public:
    void BuildFloor() override
    {
        for(size_t i = 0; i < house->GetHouseWidth(); ++i) {
            house->look[house->GetHouseHeight() - 1][i] = '#';
        }
    }

    void BuildWalls() override
    {
        for(size_t i = 0; i < house->GetHouseWidth(); ++i) {
            house->look[2][i] = '#';
            house->look[house->GetHouseHeight() - 1][i] = '#';
        }

        for(size_t i = 2; i < house->GetHouseHeight(); ++i) {
            house->look[i][0] = '#';
            house->look[i][house->GetHouseWidth() - 1] = '#';
        }
    }

    void BuildRoof() override
    {
        house->look[0][4] = '#';
        house->look[0][5] = '#';
        house->look[0][6] = '#';
        house->look[0][7] = '#';
        house->look[0][8] = '#';
        house->look[0][9] = '#';
        house->look[1][2] = '#';
        house->look[1][3] = '#';
        house->look[1][4] = '#';
        house->look[1][9] = '#';
        house->look[1][10] = '#';
        house->look[1][11] = '#';
    }

    void BuildPipe() override
    {
        house->look[0][house->GetHouseWidth() - 3] = '#';
        house->look[1][house->GetHouseWidth() - 3] = '#';
    }
};

class HouseBuilderB : public HouseBuilder
{
public:
    void BuildFloor() override
    {
        for(size_t i = 0; i < house->GetHouseWidth(); ++i) {
            house->look[house->GetHouseHeight() - 1][i] = '#';
        }
    }

    void BuildWalls() override
    {
        for(size_t i = 0; i < house->GetHouseWidth(); ++i) {
            house->look[2][i] = '#';
            house->look[house->GetHouseHeight() - 1][i] = '#';
        }

        for(size_t i = 2; i < house->GetHouseHeight(); ++i) {
            house->look[i][0] = '#';
            house->look[i][house->GetHouseWidth() - 1] = '#';
        }
    }

    void BuildWindows() override
    {
        house->look[4][3] = '#';
        house->look[4][4] = '#';
        house->look[4][6] = '#';
        house->look[4][7] = '#';

    }

    void BuildRoof() override
    {
        house->look[0][4] = '#';
        house->look[0][5] = '#';
        house->look[0][6] = '#';
        house->look[0][7] = '#';
        house->look[0][8] = '#';
        house->look[0][9] = '#';
        house->look[1][2] = '#';
        house->look[1][3] = '#';
        house->look[1][4] = '#';
        house->look[1][9] = '#';
        house->look[1][10] = '#';
        house->look[1][11] = '#';
    }
};

class HouseBuilderC : public HouseBuilder
{
public:
    void BuildFloor() override
    {
        for(size_t i = 0; i < house->GetHouseWidth(); ++i) {
            house->look[house->GetHouseHeight() - 1][i] = '#';
        }
    }

    void BuildWalls() override
    {
        for(size_t i = 0; i < house->GetHouseWidth(); ++i) {
            house->look[2][i] = '#';
            house->look[house->GetHouseHeight() - 1][i] = '#';
        }

        for(size_t i = 2; i < house->GetHouseHeight(); ++i) {
            house->look[i][0] = '#';
            house->look[i][house->GetHouseWidth() - 1] = '#';
        }
    }

    void BuildWindows() override
    {
        house->look[4][3] = '#';
        house->look[4][4] = '#';
        house->look[4][6] = '#';
        house->look[4][7] = '#';

    }
    
    void BuildDoor() override
    {
        house->look[4][10] = '#';
        house->look[4][11] = '#';
        house->look[5][10] = '#';
        house->look[5][11] = '#';
    }

    void BuildRoof() override
    {
        house->look[0][4] = '#';
        house->look[0][5] = '#';
        house->look[0][6] = '#';
        house->look[0][7] = '#';
        house->look[0][8] = '#';
        house->look[0][9] = '#';
        house->look[1][2] = '#';
        house->look[1][3] = '#';
        house->look[1][4] = '#';
        house->look[1][9] = '#';
        house->look[1][10] = '#';
        house->look[1][11] = '#';
    }

    void BuildPipe() override
    {
        house->look[0][house->GetHouseWidth() - 3] = '#';
        house->look[1][house->GetHouseWidth() - 3] = '#';
    }
};

class HouseDirector
{
public:
    std::shared_ptr<House> CreateHouse(HouseBuilder& builder)
    {
        builder.CreateHouse();

        builder.BuildFloor();
        builder.BuildWalls();
        builder.BuildWindows();
        builder.BuildDoor();
        builder.BuildRoof();
        builder.BuildPipe();

        return builder.GetHouse();
    }
};
