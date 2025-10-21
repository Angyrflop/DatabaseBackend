#include "logginHandler.hpp"
#include <config.hpp>


Logger::Logger(LogType type)
    : m_type(type)
{
}

Logger::~Logger()
{
    Write();
}

void Logger::Write()
{
    std::ofstream oFile(Config::LOG_FILE, std::ios::app);
    if (!oFile.is_open())
    {
        std::cerr << "[Logger] Failed to open log file.\n";
        return;
    }


    std::time_t now = std::time(nullptr);
    char buf[32];
    std::tm timeinfo{};

    #ifdef _WIN32
    localtime_s(&timeinfo, &now);     // Windows / MSVC
    #else
    localtime_r(&now, &timeinfo);     // POSIX (Linux, macOS)
    #endif

    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);

    // Prefix
    std::string prefix;
    switch (m_type)
    {
    case LogType::INFO: prefix = "[INFO] "; break;
    case LogType::WARNING: prefix = "[WARN] "; break;
    case LogType::ERROR: prefix = "[ERROR] "; break;
    }

    std::string msg = m_ss.str();

    // File
    oFile << buf << " " << prefix << msg << '\n';

    // Console
    if (m_type == LogType::ERROR)
        std::cerr << prefix << msg << '\n';
    else
        std::cout << prefix << msg << '\n';
}
