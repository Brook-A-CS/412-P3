#pragma once
// #include <iostream>
#include <queue>
#include <vector>
#include "Request.h"
#include "WebServer.h"


class LoadBalancer {
    private:
        std::queue<Request> requestQueue;
        std::vector<WebServer> servers;
        int currentTime = 0;

        // bool isBlocked();
        void balanceLoad();
    public:
        LoadBalancer(int numServers);
        void addRequest(Request r);
        void increment();
        int queue_size() const {  return requestQueue.size(); };
        int server_size() const {  return servers.size(); };
        int getTime() const { return currentTime; };

};