#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

class Logger
{
public:
    enum class LogLevel { Info = 0, Warn, Debug, Error };

    static inline std::ofstream s_File;
    static inline bool s_bShouldFormat = true;
    static std::string getType(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Warn:
                return "WARN";

            case LogLevel::Error:
                return "ERROR";
        };

        return (level == LogLevel::Debug ? "DEBUG" : "INFO");
    };

    static std::string getColor(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Warn:
                return "\033[1;33m";

            case LogLevel::Error:
                return "\033[1;31m";
        };

        return "\033[1;37m";
    };

    static void log(LogLevel level, const std::string& message)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm; 
#if _WIN32
        localtime_s(&now_tm, &now_time_t);
#else
        localtime_r(&now_time_t, &now_tm);
#endif

        const std::string& type = Logger::getType(level);

        std::stringstream buffer;
        buffer << std::put_time(&now_tm, "%Y-%m-%d %T");

        bool bIsOpen = Logger::s_File.is_open();
        const std::string& fullDate = !bIsOpen ? "NO LOG FILE! -" : std::format("[{} {}]", buffer.str(), type);


        std::string log = std::format("{} {}", fullDate, message);
        if (bIsOpen)
            Logger::s_File << log << "\n";

        if (s_bShouldFormat)
        {
            log = Logger::getColor(level).append(log).append("\033[0m");
        };

        std::cout << log << "\n";
    };
};

#endif // !LOGGER_HPP
