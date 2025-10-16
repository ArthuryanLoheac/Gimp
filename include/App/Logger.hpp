#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <memory>

namespace MyGimp {
class Logger {
 public:
    enum class Level {
        DEBUG,
        INFO,
        WARN,
        ERROR,
    };

    // Initialize the logger
    static void initialize();

    // Shutdown the logger
    static void shutdown();

    // Log functions
    static void log(Level level, const std::string& message);
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void debug(const std::string& message);
    static void error(const std::string& message);

 private:
    static bool initialized;
    static std::string getCurrentTimestamp();
    static std::string levelToString(Level level);
};
}  // namespace MyGimp

#define LOG_INFO(msg) MyGimp::Logger::info(msg)
#define LOG_DEBUG(msg) MyGimp::Logger::debug(msg)
#define LOG_WARN(msg) MyGimp::Logger::warn(msg)
#define LOG_ERROR(msg) MyGimp::Logger::error(msg)

// Always available initialization macros
#define LOG_INIT() MyGimp::Logger::initialize()
#define LOG_SHUTDOWN() MyGimp::Logger::shutdown()
