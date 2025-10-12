#include "Logger.hpp"
#include <iostream>
#include <sstream>
#include <mutex>
#include <string>
#include <memory>

namespace MyGimp {
bool Logger::initialized = false;

#ifdef USE_SPDLOG
std::shared_ptr<spdlog::logger> Logger::logger = nullptr;
#endif

void Logger::initialize() {
    if (initialized) {
        return;
    }

#ifdef USE_SPDLOG
    try {
        // Create a colored console logger with spdlog
        logger = spdlog::stdout_color_mt("MyGimp");
        logger->set_level(spdlog::level::debug);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
        logger->info("Logger initialized with spdlog");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        // Fallback to console logging
        logger = nullptr;
    }
#else
    // Console fallback initialization message
    std::cout << "[" << getCurrentTimestamp()
        << "] [MyGimp] [INFO] Logger initialized with console fallback"
        << std::endl;
#endif

    initialized = true;
}

void Logger::shutdown() {
    if (!initialized) {
        return;
    }

#ifdef USE_SPDLOG
    if (logger) {
        logger->info("Logger shutting down");
        spdlog::shutdown();
    } else {
        std::cout << "[" << getCurrentTimestamp() <<
            "] [MyGimp] [INFO] Logger shutting down" << std::endl;
    }
#else
    std::cout << "[" << getCurrentTimestamp()
        << "] [MyGimp] [INFO] Logger shutting down" << std::endl;
#endif

    initialized = false;
}

void Logger::log(Level level, const std::string& message) {
    if (!initialized) {
        initialize();
    }

#ifdef USE_SPDLOG
    if (logger) {
        switch (level) {
            case Level::INFO:
                logger->info(message);
                break;
            case Level::WARN:
                logger->warn(message);
                break;
            case Level::ERROR:
                logger->error(message);
                break;
            case Level::DEBUG:
                logger->debug(message);
                break;
        }
        return;
    }
#endif

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
