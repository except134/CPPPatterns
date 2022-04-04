#pragma once

class GameCommand
{
public:
    virtual ~GameCommand() = default;

    virtual void Run() = 0;
};

