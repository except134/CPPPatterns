// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

void LoggerFile::OpenLogFile(const std::string& FN)
{
    logOut.open(FN, std::ios_base::out);
}

void LoggerFile::CloseLogFile()
{
    if(logOut.is_open()) {
        logOut.close();
    }
}

void LoggerFile::WriteToLog(const std::string& str)
{
    if(logOut.is_open()) {
        logOut << str << std::endl;
    }
}

void LoggerFile::WriteToLog(const std::string& str, int n)
{
    if(logOut.is_open()) {
        logOut << str << n << std::endl;
    }
}

void LoggerFile::WriteToLog(const std::string& str, double d)
{
    if(logOut.is_open()) {
        logOut << str << d << std::endl;
    }
}

