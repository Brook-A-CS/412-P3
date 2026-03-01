#include <iostream>
#include <vector>

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

Request RequestGenerator::generateRequest(bool generate_log) {
    std::uniform_int_distribution<int> timeDist(5, 500); 
    std::uniform_int_distribution<int> jobDist(0, 1);

    std::string ipIn = generateRandomIP();
    std::string ipOut = generateRandomIP();
    int time = timeDist(rng);
    char jobType = (jobDist(rng) == 0) ? 'P' : 'S';

    if (generate_log) {
        std::cout << Color::CYAN << "[INFO] " << Color::RESET 
              << "Generated Request - "
              << "IP In: " << ipIn 
              << ", IP Out: " << ipOut
              << ", Time: " << time 
              << ", Job Type: " << jobType 
              << std::endl;
    }

    return Request(ipIn, ipOut, time, jobType);
}

std::vector<Request> RequestGenerator::generateRequests(int count) {
    std::vector<Request> rqs;

    std::cout << Color::CYAN << "[INFO] " << Color::RESET 
              << "Generating a batch of " << count << " requests:\n";

    for (int i = 0; i < count; i++) {
        rqs.push_back(generateRequest());
    }

    return rqs;
}