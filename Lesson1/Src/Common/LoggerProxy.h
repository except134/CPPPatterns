#pragma once

class LoggerProxy : public ILogger, public SingletonStatic<LoggerProxy>, public NonCopyable, public NonMoveable
{
public:
    virtual ~LoggerProxy()
    {
        CloseLogFile();
    }

    void SetReal(ILogger* plogger);

    void OpenLogFile(const std::string& FN) override;
    void CloseLogFile() override;
    void WriteToLog(const std::string& str) override;
    void WriteToLog(const std::string& str, int n) override;
    void WriteToLog(const std::string& str, double d) override;

private:
    const std::tm* GetLocalTime();

private:
    std::tm		localTime{};
    ILogger*    logger{};
};

