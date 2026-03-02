#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Firewall.h"
#include "Color.h"

uint32_t Firewall::parseIP(const std::string& ip) {
    uint32_t result = 0;
    std::stringstream ss(ip);
    std::string octet;
    int count = 0;
    while (std::getline(ss, octet, '.')) {
        result = (result << 8) | std::stoi(octet);
        count++;
    }
    if (count != 4) throw std::invalid_argument("Invalid IP address: " + ip);
    return result;
}

std::pair<uint32_t, uint32_t> Firewall::parseCIDR(const std::string& cidr) {
    size_t slash = cidr.find('/');
    if (slash == std::string::npos) throw std::invalid_argument("Invalid CIDR: " + cidr);
    uint32_t ip = parseIP(cidr.substr(0, slash));
    int prefix = std::stoi(cidr.substr(slash + 1));
    uint32_t mask = prefix == 0 ? 0u : (~0u << (32 - prefix));
    return {ip & mask, mask};
}

void Firewall::blockRange(const std::string& cidr) {
    auto [network, mask] = parseCIDR(cidr);
    blockedRanges.push_back({network, mask, cidr});
    std::cout << Color::RED << "[FIREWALL] " << Color::RESET
              << "Blocked range added: " << cidr << std::endl;
}

bool Firewall::isBlocked(const std::string& ip) const {
    uint32_t addr = parseIP(ip);
    for (const auto& range : blockedRanges) {
        if ((addr & range.mask) == range.network) return true;
    }
    return false;
}

void Firewall::printRules() const {
    std::cout << Color::RED << "[FIREWALL] " << Color::RESET
              << "Active blocked ranges (" << blockedRanges.size() << "):\n";
    for (const auto& r : blockedRanges) {
        std::cout << "  - " << r.cidr << "\n";
    }
}
