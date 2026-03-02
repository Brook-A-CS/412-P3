#pragma once
#include <string>
#include <vector>

/// @brief IP prefix-based firewall that drops requests from blocked address ranges.
class Firewall {
    private:
        std::vector<std::string> blockedPrefixes;

    public:
        /// @brief Adds an IP prefix to the block list.
        ///        Any request whose source IP starts with this prefix will be dropped.
        /// @param prefix IP prefix string (e.g. "10." blocks all 10.x.x.x addresses)
        void blockRange(const std::string& prefix);

        /// @brief Checks whether the given IP address matches any blocked prefix.
        /// @param ip The source IP address to check
        /// @return true if the IP is blocked, false otherwise
        bool isBlocked(const std::string& ip) const;

        /// @brief Logs all currently active blocked prefixes.
        void printRules() const;
};
