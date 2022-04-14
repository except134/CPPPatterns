#pragma once

class Mediator
{
public:
    void Add(std::shared_ptr<AbstractLevelGUI>& g);
    void SendMessage(std::unique_ptr<TankMessage>&& mes);

private:
    std::shared_ptr<AbstractLevelGUI> gui;
};

