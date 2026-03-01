#include <iostream>
#include <random>
#include <vector>
#include "LoadBalancer.h"
#include "RequestGenerator.h"

std::random_device rd;
std::mt19937 gen(rd());

int main() {

    LoadBalancer LB(1);
    RequestGenerator RG;

    const int TOTAL_TIME = 10000;

    for(int t = 0; t < TOTAL_TIME; t++) {
        
        std::uniform_int_distribution<> distrib(10, 20);
        int num_rqs = distrib(gen);

        std::vector<Request> rqs = RG.generateRequests(num_rqs);
        for (Request& rq : rqs) {
            LB.addRequest(rq);
        }

        LB.increment();
    }

    return 0;
}