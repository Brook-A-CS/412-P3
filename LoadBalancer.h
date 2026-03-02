#pragma once
#include <queue>
#include <vector>
#include "Request.h"
#include "WebServer.h"
#include "Firewall.h"

/// @brief Manages a pool of WebServers and a queue of incoming Requests.
///
/// Every 30 clock cycles, balanceLoad() is called to add or remove servers:
///  - If queue > 80 * servers: add a server
///  - If queue < 50 * servers: remove a server (minimum 1)
class LoadBalancer {
    private:
        std::queue<Request> requestQueue;
        std::vector<WebServer> servers;
        Firewall firewall;
        std::string name;
        int currentTime = 0;

        int totalProcessed  = 0;
        int totalBlocked    = 0;
        int serversAdded    = 0;
        int serversRemoved  = 0;
        int peakQueueSize   = 0;
        int peakServerCount = 0;

        /// @brief Checks queue size against server capacity thresholds and
        ///        adds or removes a server if needed.
        void balanceLoad();

    public:
        /// @brief Constructs a LoadBalancer with the given number of servers.
        /// @param numServers Initial number of WebServers to create
        /// @param name Label used in logs to identify this instance (e.g. "Stream", "Process")
        LoadBalancer(int numServers, const std::string& name = "LB");

        /// @brief Adds a request to the queue after firewall inspection.
        ///        Requests matching a blocked prefix are silently dropped.
        /// @param r The incoming Request
        void addRequest(Request r);

        /// @brief Advances the simulation by one clock cycle.
        ///        Dispatches queued requests to free servers, ticks all servers,
        ///        and triggers load balancing every 30 ticks.
        void increment();

        /// @brief Logs a full end-of-run summary to terminal and log file.
        void printSummary() const;

        /// @brief Adds an IP prefix to the firewall block list.
        /// @param prefix IP prefix to block (e.g. "10.")
        void blockIP(const std::string& prefix) { firewall.blockRange(prefix); };

        /// @brief Logs all active firewall rules.
        void printFirewallRules() const { firewall.printRules(); };

        /// @brief Returns the current number of queued requests.
        int queue_size() const { return requestQueue.size(); };

        /// @brief Returns the current number of active servers.
        int server_size() const { return servers.size(); };

        /// @brief Returns the current simulation tick.
        int getTime() const { return currentTime; };
};
