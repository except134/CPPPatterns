// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

void LoggerProxy::SetReal(ILogger* plogger)
{
    logger = plogger;
}

void __fastcall LoggerProxy::OpenLogFile(const std::string& FN)
{
    if(logger)
        logger->OpenLogFile(FN);
}

void LoggerProxy::CloseLogFile()
{
    if(logger)
        logger->CloseLogFile();
}

const std::tm* LoggerProxy::GetLocalTime()
{
    auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    localtime_s(&localTime, &in_time_t);
    return &localTime;
}

std::ostream& operator<< (std::ostream& stream, const std::tm* tm)
{
    return stream
        << std::setfill('0') << std::setw(2) << tm->tm_mday << '.'
        << std::setfill('0') << std::setw(2) << tm->tm_mon + 1 << '.'
        << 1900 + tm->tm_year << ' '
        << std::setfill('0') << std::setw(2) << tm->tm_hour << ':'
        << std::setfill('0') << std::setw(2) << tm->tm_min << ':'
        << std::setfill('0') << std::setw(2) << tm->tm_sec;
}

void __fastcall LoggerProxy::WriteToLog(const std::string& str)
{
    if(!logger)
        return;
    std::stringstream s;
    s << '[' << GetLocalTime() << "] " << str;
    logger->WriteToLog(s.str());
}

void __fastcall LoggerProxy::WriteToLog(const std::string& str, int n)
{
    if(!logger)
        return;
    std::stringstream s;
    s << '[' << GetLocalTime() << "] " << str;
    logger->WriteToLog(s.str(), n);
}

void __fastcall LoggerProxy::WriteToLog(const std::string& str, double d)
{
    if(!logger)
        return;
    std::stringstream s;
    s << '[' << GetLocalTime() << "] " << str;
    logger->WriteToLog(s.str(), d);
}

