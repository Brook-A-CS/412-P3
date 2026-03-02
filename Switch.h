#pragma once
#include "LoadBalancer.h"
#include "Request.h"

/// @brief Routes incoming Requests to one of two LoadBalancers based on job type.
///
/// Job type 'S' (Streaming) is routed to the stream LoadBalancer.
/// Job type 'P' (Processing) is routed to the process LoadBalancer.
/// Both load balancers operate and balance independently.
class Switch {
    private:
        LoadBalancer streamLB;
        LoadBalancer processLB;

    public:
        /// @brief Constructs a Switch with separate server counts for each job type.
        /// @param streamServers Initial number of servers for streaming requests
        /// @param processServers Initial number of servers for processing requests
        Switch(int streamServers, int processServers);

        /// @brief Routes a request to the appropriate LoadBalancer based on job type.
        ///        Also applies firewall rules from both load balancers.
        /// @param r The incoming request
        void addRequest(Request r);

        /// @brief Advances both LoadBalancers by one clock cycle.
        void increment();

        /// @brief Adds an IP prefix to the block list of both LoadBalancers.
        /// @param prefix IP prefix to block (e.g. "10.")
        void blockIP(const std::string& prefix);

        /// @brief Prints a summary for both LoadBalancers.
        void printSummary() const;
};
