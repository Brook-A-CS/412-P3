#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct IPRange {
    uint32_t network;
    uint32_t mask;
    std::string cidr;
};

class Firewall {
    private:
        std::vector<IPRange> blockedRanges;

        static uint32_t parseIP(const std::string& ip);
        static std::pair<uint32_t, uint32_t> parseCIDR(const std::string& cidr);

    public:
        void blockRange(const std::string& cidr);
        bool isBlocked(const std::string& ip) const;
        void printRules() const;
};
