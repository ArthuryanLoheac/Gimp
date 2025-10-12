#include "App/Logger.hpp"
#include <iostream>
#include <sstream>
#include <mutex>
#include <string>
#include <memory>

namespace MyGimp {
bool Logger::initialized = false;

void Logger::initialize() {
    if (initialized) {
        return;
    }

    // Console fallback initialization message
    std::cout << "[" << getCurrentTimestamp()
        << "] [MyGimp] [INFO] Logger initialized with console fallback"
        << std::endl;

    initialized = true;
}

void Logger::shutdown() {
    if (!initialized) {
        return;
    }

    std::cout << "[" << getCurrentTimestamp()
        << "] [MyGimp] [INFO] Logger shutting down" << std::endl;

    initialized = false;
}

void Logger::log(Level level, const std::string& message) {
    if (!initialized) {
        initialize();
    }

    // Fallback to console output
    static std::mutex console_mutex;
    std::lock_guard<std::mutex> lock(console_mutex);

    std::ostream* output = (level == Level::ERROR) ? &std::cerr : &std::cout;

    *output << "[" << getCurrentTimestamp() << "] [MyGimp] ["
            << levelToString(level) << "] " << message << std::endl;
}

void Logger::info(const std::string& message) {
    log(Level::INFO, message);
}

void Logger::warn(const std::string& message) {
    log(Level::WARN, message);
}

void Logger::error(const std::string& message) {
    log(Level::ERROR, message);
}

void Logger::debug(const std::string& message) {
    log(Level::DEBUG, message);
}

std::string Logger::getCurrentTimestamp() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::levelToString(Level level) {
    switch (level) {
        case Level::INFO:  return "INFO";
        case Level::WARN:  return "WARN";
        case Level::ERROR: return "ERROR";
        case Level::DEBUG: return "DEBUG";
        default:           return "UNKNOWN";
    }
}
}  // namespace MyGimp
