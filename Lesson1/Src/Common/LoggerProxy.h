#pragma once

class LoggerProxy : public ILogger, public SingletonStatic<LoggerProxy>, public NonCopyable, public NonMoveable
{
public:
    void SetReal(ILogger* plogger);

    void __fastcall OpenLogFile(const std::string& FN) override;
    void CloseLogFile() override;
    void __fastcall WriteToLog(const std::string& str) override;
    void __fastcall WriteToLog(const std::string& str, int n) override;
    void __fastcall WriteToLog(const std::string& str, double d) override;

private:
    const std::tm* GetLocalTime();

private:
    std::tm		localTime{};
    ILogger*    logger{};
};

