#include <iostream>
#include "LoadBalancer.h"
#include "WebServer.h"
#include "Request.h"
#include "Color.h"

const int WAIT_BETWEEN_REBALANCING = 30;

LoadBalancer::LoadBalancer(int numServers) {
    servers.resize(numServers);
}

void LoadBalancer::addRequest(Request r) {
    requestQueue.push(r);
}

void LoadBalancer::increment() {
    for (WebServer& server : servers) {
        if (server.isFree() && !requestQueue.empty()) {
            server.processRequest(std::move(requestQueue.front()));
            requestQueue.pop();
        }
        server.tick();
    }

    if (currentTime % WAIT_BETWEEN_REBALANCING == 0) balanceLoad();
    currentTime += 1;
}

void LoadBalancer::balanceLoad() {
    if(requestQueue.size() > 80 * servers.size()) {
        
        servers.push_back(WebServer());
        std::cout << Color::GREEN << "[INFO] " << Color::RESET <<
        "Num servers increased by 1 for a total of " << server_size() << std::endl;
    }

    if(requestQueue.size() < 50 * servers.size()) {
        servers.pop_back();

        std::cout << Color::CYAN << "[INFO] " << Color::RESET <<
        "Num servers increased by 1 for a total of " << server_size() << std::endl;
    };

    
}