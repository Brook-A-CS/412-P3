#include <iostream>

#include "RequestGenerator.h"
#include "Color.h"

RequestGenerator::RequestGenerator() {
    std::random_device rd;
    rng.seed(rd());
}

std::string RequestGenerator::generateRandomIP() {
    std::uniform_int_distribution<int> octetDist(0, 255);
    
    std::string ip = std::to_string(octetDist(rng)) + "." +
                     std::to_string(octetDist(rng)) + "." +
                     std::to_string(octetDist(rng)) + "." +
                     std::to_string(octetDist(rng));
                     
    return ip;
}

Request RequestGenerator::generateRequest() {
    std::uniform_int_distribution<int> timeDist(5, 500); 
    std::uniform_int_distribution<int> jobDist(0, 1);

    std::string ipIn = generateRandomIP();
    std::string ipOut = generateRandomIP();
    int time = timeDist(rng);
    char jobType = (jobDist(rng) == 0) ? 'P' : 'S';

    std::cout << Color::CYAN << "[INFO] " << Color::RESET 
          << "Generated Request - "
          << "IP In: " << ipIn 
          << ", IP Out: " << ipOut
          << ", Time: " << time 
          << ", Job Type: " << jobType 
          << std::endl;
    
    return Request(ipIn, ipOut, time, jobType);
}