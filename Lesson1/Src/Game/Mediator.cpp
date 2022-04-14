// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

void Mediator::Add(std::shared_ptr<AbstractLevelGUI>& g)
{
    gui = g;
}

void Mediator::SendMessage(std::unique_ptr<TankMessage>&& mes)
{
    gui->AddMessage(std::move(mes));
}

