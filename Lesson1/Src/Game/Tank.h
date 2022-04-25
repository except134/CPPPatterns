#pragma once

class Tank : public DestroyableGroundObject
{
public:
    Tank() = default;
    Tank(std::shared_ptr<Mediator> med) : 
        mediator(med)
    {
    }

    bool IsInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override
    {
        return score;
    }

    Tank* Clone() const override
    {
        return new Tank(*this);
    }

    void Draw() const override;
    void SendMessage() const;

private:
    Tank(const Tank& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        width = rhs.width;
        mediator = rhs.mediator;
    }

    const uint16_t score = 30;
    std::shared_ptr<Mediator> mediator;
    static std::vector<std::string> messages;
};

