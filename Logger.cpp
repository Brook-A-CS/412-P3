#include <iostream>
#include <iomanip>
#include <sstream>
#include "Logger.h"
#include "Color.h"

Logger& Logger::get() {
    static Logger instance;
    return instance;
}

void Logger::open(const std::string& filename) {
    logFile.open(filename);
}

std::string Logger::tickStr() const {
    std::ostringstream ss;
    ss << "[T=" << std::setw(5) << std::setfill('0') << tick << "]";
    return ss.str();
}

void Logger::toFile(const std::string& tag, const std::string& msg) {
    if (logFile.is_open())
        logFile << tickStr() << " [" << tag << "] " << msg << "\n";
}

void Logger::detail(const std::string& msg) {
    toFile("DETAIL", msg);
}

void Logger::info(const std::string& msg) {
    toFile("INFO", msg);
    std::cout << Color::CYAN << "[INFO] " << Color::RESET << msg << "\n";
}

void Logger::warn(const std::string& msg) {
    toFile("WARN", msg);
    std::cout << Color::YELLOW << "[WARN] " << Color::RESET << msg << "\n";
}

void Logger::alert(const std::string& msg) {
    toFile("ALERT", msg);
    std::cout << Color::RED << "[ALERT] " << Color::RESET << msg << "\n";
}

void Logger::summary(const std::string& msg) {
    toFile("SUMMARY", msg);
    std::cout << Color::BLUE << "[SUMMARY] " << Color::RESET << msg << "\n";
}
