#include <iostream>
#include "LoadBalancer.h"
#include "WebServer.h"
#include "Request.h"
#include "Logger.h"

const int WAIT_BETWEEN_REBALANCING = 30;
const int STATUS_INTERVAL = 1000;

LoadBalancer::LoadBalancer(int numServers) {
    servers.resize(numServers);
    peakServerCount = numServers;
    Logger::get().info("LoadBalancer started with " + std::to_string(numServers) + " servers");
}

void LoadBalancer::addRequest(Request r) {
    if (firewall.isBlocked(r.getIPIn())) {
        totalBlocked++;
        Logger::get().detail("Firewall dropped: " + r.getIPIn() + " > " + r.getIpOut());
        return;
    }
    requestQueue.push(r);
    int qs = requestQueue.size();
    if (qs > peakQueueSize) peakQueueSize = qs;
}

void LoadBalancer::increment() {
    Logger::get().setTick(currentTime);

    for (WebServer& server : servers) {
        if (server.isFree() && !requestQueue.empty()) {
            Request r = requestQueue.front();
            Logger::get().detail("Dispatched " + r.getIPIn() + " > " + r.getIpOut()
                + " | job=" + r.getJob()
                + " time=" + std::to_string(r.getTime())
                + " queue=" + std::to_string(requestQueue.size() - 1));
            server.processRequest(std::move(r));
            requestQueue.pop();
            totalProcessed++;
        }
        server.tick();
    }

    if (currentTime % WAIT_BETWEEN_REBALANCING == 0) balanceLoad();

    if (currentTime % STATUS_INTERVAL == 0 && currentTime > 0) {
        Logger::get().info("Status | queue=" + std::to_string(queue_size())
            + " servers=" + std::to_string(server_size())
            + " processed=" + std::to_string(totalProcessed)
            + " blocked=" + std::to_string(totalBlocked));
    }

    currentTime++;
}

void LoadBalancer::balanceLoad() {
    int qs = requestQueue.size();
    int ss = servers.size();

    if (qs > 80 * ss) {
        servers.push_back(WebServer());
        serversAdded++;
        if ((int)servers.size() > peakServerCount) peakServerCount = servers.size();
        Logger::get().info("Server added   | queue=" + std::to_string(qs)
            + " | total=" + std::to_string(server_size()));

    } else if (qs < 50 * ss && ss > 1) {
        servers.pop_back();
        serversRemoved++;
        Logger::get().warn("Server removed | queue=" + std::to_string(qs)
            + " | total=" + std::to_string(server_size()));
            
    } else {
        Logger::get().detail("Balance check  | queue=" + std::to_string(qs)
            + " servers=" + std::to_string(ss) + " | no change");
    }
}

void LoadBalancer::printSummary() const {
    Logger::get().summary("=== Load Balancer Summary ===");
    Logger::get().summary("Total clock cycles  : " + std::to_string(currentTime));
    Logger::get().summary("Requests processed  : " + std::to_string(totalProcessed));
    Logger::get().summary("Requests blocked    : " + std::to_string(totalBlocked));
    Logger::get().summary("Servers added       : " + std::to_string(serversAdded));
    Logger::get().summary("Servers removed     : " + std::to_string(serversRemoved));
    Logger::get().summary("Peak queue size     : " + std::to_string(peakQueueSize));
    Logger::get().summary("Peak server count   : " + std::to_string(peakServerCount));
    Logger::get().summary("Final queue size    : " + std::to_string(requestQueue.size()));
    Logger::get().summary("Final server count  : " + std::to_string(servers.size()));
}
