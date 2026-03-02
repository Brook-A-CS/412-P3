#pragma once
#include <string>
#include <vector>

class Firewall {
    private:
        std::vector<std::string> blockedPrefixes;

    public:
        void blockRange(const std::string& prefix);
        bool isBlocked(const std::string& ip) const;
        void printRules() const;
};
