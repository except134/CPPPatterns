#pragma once

class Tank : public DestroyableGroundObject
{
public:
    Tank(std::shared_ptr<Mediator> med) : 
        mediator(med)
    {
    }

    bool IsInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override
    {
        return score;
    }

    void Draw() const override;
    void SendMessage() const;

private:
    const uint16_t score = 30;
    std::shared_ptr<Mediator> mediator;
    static std::vector<std::string> messages;
};

