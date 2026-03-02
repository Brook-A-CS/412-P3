#pragma once
#include <queue>
#include <vector>
#include "Request.h"
#include "WebServer.h"
#include "Firewall.h"


class LoadBalancer {
    private:
        std::queue<Request> requestQueue;
        std::vector<WebServer> servers;
        Firewall firewall;
        int currentTime = 0;

        int totalProcessed  = 0;
        int totalBlocked    = 0;
        int serversAdded    = 0;
        int serversRemoved  = 0;
        int peakQueueSize   = 0;
        int peakServerCount = 0;

        void balanceLoad();
    public:
        LoadBalancer(int numServers);
        void addRequest(Request r);
        void increment();
        void printSummary() const;
        void blockIP(const std::string& cidr) { firewall.blockRange(cidr); };
        void printFirewallRules() const { firewall.printRules(); };
        int queue_size() const { return requestQueue.size(); };
        int server_size() const { return servers.size(); };
        int getTime() const { return currentTime; };

};