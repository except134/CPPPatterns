#pragma once

class ILogger
{
public:
    virtual void OpenLogFile(const std::string& FN) = 0;
    virtual void CloseLogFile() = 0;
    virtual void WriteToLog(const std::string& str) = 0;
    virtual void WriteToLog(const std::string& str, int n) = 0;
    virtual void WriteToLog(const std::string& str, double d) = 0;
};

