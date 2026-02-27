#pragma once
#include "Request.h"
#include <random>
#include <string>

class RequestGenerator {
    private:
        std::mt19937 rng; 
        std::string generateRandomIP(); 

    public:
        RequestGenerator();
        Request generateRequest();
};