#pragma once

class LoggerFile : public ILogger, public SingletonStatic<LoggerFile>, public NonCopyable, public NonMoveable
{
public:
    ~LoggerFile()
    {
        CloseLogFile();
    }

    void OpenLogFile(const std::string& FN) override;
    void CloseLogFile() override;
    void WriteToLog(const std::string& str) override;
    void WriteToLog(const std::string& str, int n) override;
    void WriteToLog(const std::string& str, double d) override;

private:
    std::ofstream   logOut;
};

