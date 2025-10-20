#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>

enum class LogType { INFO, WARNING, ERROR };

class Logger
{
public:
    explicit Logger(LogType type);
    ~Logger();

    template<typename T>
    Logger& operator<<(const T& value)
    {
        m_ss << value;
        return *this;
    }

private:
    void Write();
    LogType m_type;
    std::ostringstream m_ss;
};
