#pragma once
#include "Request.h"
#include <random>
#include <string>
#include <vector>

class RequestGenerator {
    private:
        std::mt19937 rng; 
        std::string generateRandomIP(); 

    public:
        RequestGenerator();
        Request generateRequest(bool generate_log = true);
        std::vector<Request> generateRequests(int count);

};