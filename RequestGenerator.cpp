#include <vector>
#include "RequestGenerator.h"
#include "Logger.h"

RequestGenerator::RequestGenerator() {
    std::random_device rd;
    rng.seed(rd());
}

std::string RequestGenerator::generateRandomIP() {
    std::uniform_int_distribution<int> octetDist(0, 255);
    std::uniform_int_distribution<int> chanceDist(0, 99);

    int firstOctet = (chanceDist(rng) < 10) ? 10 : octetDist(rng);

    return std::to_string(firstOctet) + "." +
           std::to_string(octetDist(rng)) + "." +
           std::to_string(octetDist(rng)) + "." +
           std::to_string(octetDist(rng));
}

Request RequestGenerator::generateRequest(bool generate_log) {
    std::uniform_int_distribution<int> streamTimeDist(3, 25);
    std::uniform_int_distribution<int> processTimeDist(25, 120);
    std::uniform_int_distribution<int> jobDist(0, 1);

    std::string ipIn  = generateRandomIP();
    std::string ipOut = generateRandomIP();
    char jobType      = (jobDist(rng) == 0) ? 'P' : 'S';
    int time          = (jobType == 'S') ? streamTimeDist(rng) : processTimeDist(rng);

    if (generate_log) {
        Logger::get().detail("Generated: " + ipIn + " > " + ipOut
            + " | time=" + std::to_string(time) + " job=" + jobType);
    }

    return Request(ipIn, ipOut, time, jobType);
}

std::vector<Request> RequestGenerator::generateRequests(int count) {
    std::vector<Request> rqs;
    for (int i = 0; i < count; i++)
        rqs.push_back(generateRequest());
    return rqs;
}