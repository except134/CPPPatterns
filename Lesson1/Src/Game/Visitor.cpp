// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

void LogVisitor::Log(const Plane& p) const
{
    std::stringstream str;

    str << std::string(__FUNCTION__);
    str << " Plane fly with speed " << p.GetSpeed();
    str << " and direction x = " << std::get<0>(p.GetDirection());
    str << ", y = " << std::get<1>(p.GetDirection());

    LoggerProxy::Instance().WriteToLog(str.str());
}

void LogVisitor::Log(const Bomb& p) const
{
    std::stringstream str;

    str << std::string(__FUNCTION__);
    str << " Bomb fly with speed " << p.GetSpeed();
    str << " and direction x = " << std::get<0>(p.GetDirection());
    str << ", y = " << std::get<1>(p.GetDirection());

    LoggerProxy::Instance().WriteToLog(str.str());
}

void LogVisitor::Log(const BombDecorator& p) const
{
    std::stringstream str;

    str << std::string(__FUNCTION__);
    str << " BombDecorator fly with speed " << p.GetSpeed();
    str << " and direction x = " << std::get<0>(p.GetDirection());
    str << ", y = " << std::get<1>(p.GetDirection());

    LoggerProxy::Instance().WriteToLog(str.str());
}


