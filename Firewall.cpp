#include "Firewall.h"
#include "Logger.h"

void Firewall::blockRange(const std::string& prefix) {
    blockedPrefixes.push_back(prefix);
    Logger::get().alert("Firewall rule added: " + prefix);
}

bool Firewall::isBlocked(const std::string& ip) const {
    for (const auto& prefix : blockedPrefixes) {
        if (ip.substr(0, prefix.size()) == prefix) return true;
    }
    return false;
}

void Firewall::printRules() const {
    Logger::get().alert("Active blocked prefixes (" + std::to_string(blockedPrefixes.size()) + "):");
    for (const auto& p : blockedPrefixes) {
        Logger::get().alert("  - " + p);
    }
}
