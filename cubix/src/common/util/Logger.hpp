#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <print>
#include <string>
#include <chrono>
#include <mutex>
#include <thread>
#include <utility>

class Logger
{
public:
    enum class LogLevel : int { Info = 0, Warn, Debug, Error };

private:
    struct LogEntry {
        LogLevel logLevel;
        std::string message;
        std::chrono::system_clock::time_point timestamp;
        bool fileOpened;

        LogEntry(const LogLevel level, std::string msg)
            : logLevel(level), message(std::move(msg)),
            timestamp(std::chrono::system_clock::now()),
            fileOpened(Logger::s_File.is_open()) {};
    };

    static inline std::vector<LogEntry> s_logQueue;
    static inline std::mutex s_logMutex;

    static inline bool s_isRunning = false;
    static inline std::thread s_thread;

public:
    static inline std::ofstream s_File;
    static inline bool s_bShouldFormat = true;

    static void initialize() {
        if (s_isRunning)
            return;

        s_isRunning = true;
        s_thread = std::thread(Logger::process);
    };

    static void shutdown() {
        if (!s_isRunning)
            return;

        s_isRunning = false;
        if (s_thread.joinable()) {
            s_thread.join();
        };
    };

    template <typename... Args>
#if __cpp_lib_format >= 202207L  // C++23 or newer
    static void log(const LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
        const std::string& message = std::format(fmt, std::forward<Args>(args)...);
#else
    static void log(const LogLevel level, const std::string& fmt, Args&&... args) {
        const std::string& message = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
#endif

        std::unique_lock lock(s_logMutex);
        s_logQueue.emplace_back(level, message);
        lock.unlock();
    };

private:
    static void process() {
        while (true) {
            std::unique_lock lock(s_logMutex);
            if (!s_isRunning && s_logQueue.empty())
                break;

            if (!s_logQueue.empty()) {
                for (const auto& logEntry : s_logQueue)
                    _out(logEntry);

                s_logQueue.clear();
            };

            lock.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        };
    };

    static std::string getType(const LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Warn:
                return "WARN";

            case LogLevel::Error:
                return "ERROR";

            default: break;
        };

        return (level == LogLevel::Debug ? "DEBUG" : "INFO");
    };

    static std::string getColor(const LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Warn:
                return "\033[1;33m";

            case LogLevel::Error:
                return "\033[1;31m";

            default: break;
        };

        return "\033[1;37m";
    };

    static void _out(const LogEntry& logEntry)
    {
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(logEntry.timestamp);
        std::tm now_tm{};
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(&now_tm, &now_time_t);
#else
        localtime_r(&now_time_t, &now_tm);
#endif

        const std::string& type = Logger::getType(logEntry.logLevel);

        std::stringstream buffer;
        buffer << std::put_time(&now_tm, "%Y-%m-%d %T");

        const std::string& fullDate = !logEntry.fileOpened ? "NO LOG FILE! -" : std::format("[{} {}]", buffer.str(), type);

        std::string log = std::format("{} {}", fullDate, logEntry.message);
        if (logEntry.fileOpened && s_File.is_open())
        {
            Logger::s_File << log << "\n";
        };

        if (s_bShouldFormat)
        {
            log = Logger::getColor(logEntry.logLevel).append(log).append("\033[0m");
        };

        std::println("{}", log);
    };
};

#endif // !LOGGER_HPP
