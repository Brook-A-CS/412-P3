#pragma once
#include "Request.h"
#include <random>
#include <string>
#include <vector>

/// @brief Generates randomized Request objects to simulate incoming network traffic.
///
/// ~10% of generated source IPs will start with "10." to demonstrate firewall filtering.
class RequestGenerator {
    private:
        std::mt19937 rng;

        /// @brief Generates a random IPv4 address string.
        std::string generateRandomIP();

    public:
        /// @brief Constructs a RequestGenerator with a random seed.
        RequestGenerator();

        /// @brief Generates a single random Request.
        /// @param generate_log If true, logs the request to the detail log
        /// @return A newly constructed Request
        Request generateRequest(bool generate_log = true);

        /// @brief Generates a batch of random Requests.
        /// @param count Number of requests to generate
        /// @return Vector of generated requests
        std::vector<Request> generateRequests(int count);
};
