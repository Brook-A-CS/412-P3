#include <iostream>
#include <fstream>
#include <random>
#include "Switch.h"
#include "RequestGenerator.h"
#include "Logger.h"


// Panda Software Solutions Inc Load Balancer
// All rights reserved
int main() {

    // Config defaults
    int totalTime    = 10000;
    int numServersS  = 5;
    int numServersP  = 5;
    float reqChance  = 0.10f;
    std::string logFile      = "loadbalancer.log";
    std::string blockedRange = "10.";

    // Load config.txt
    std::ifstream cfgFile("config.txt");
    std::string line;
    while (std::getline(cfgFile, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);
        if      (key == "TOTAL_TIME")     totalTime    = std::stoi(val);
        else if (key == "NUM_SERVERS_S")  numServersS  = std::stoi(val);
        else if (key == "NUM_SERVERS_P")  numServersP  = std::stoi(val);
        else if (key == "REQUEST_CHANCE") reqChance    = std::stof(val);
        else if (key == "LOG_FILE")       logFile      = val;
        else if (key == "BLOCKED_RANGE")  blockedRange = val;
    }

    std::cout << "Total simulation time [" << totalTime << "]: ";
    std::string input;
    if (std::getline(std::cin, input) && !input.empty()) totalTime = std::stoi(input);

    std::cout << "Number of stream servers [" << numServersS << "]: ";
    if (std::getline(std::cin, input) && !input.empty()) numServersS = std::stoi(input);

    std::cout << "Number of process servers [" << numServersP << "]: ";
    if (std::getline(std::cin, input) && !input.empty()) numServersP = std::stoi(input);

    Logger::get().open(logFile);
    Logger::get().info("Config: total_time=" + std::to_string(totalTime)
        + " servers_S=" + std::to_string(numServersS)
        + " servers_P=" + std::to_string(numServersP)
        + " req_chance=" + std::to_string(reqChance)
        + " task_time_S=3-25 task_time_P=25-120");

    Switch SW(numServersS, numServersP);
    SW.blockIP(blockedRange);
    RequestGenerator RG;

    int initialFill = (numServersS + numServersP) * 100;
    for (Request r : RG.generateRequests(initialFill))
        SW.addRequest(r);
    Logger::get().info("Starting queue size | stream=" + std::to_string(SW.streamQueueSize())
        + " process=" + std::to_string(SW.processQueueSize()));

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> chanceDist(0.0f, 1.0f);

    for (int t = 0; t < totalTime; t++) {
        int numReqs = (int)reqChance;
        if (chanceDist(gen) < (reqChance - numReqs)) numReqs++;
        for (int i = 0; i < numReqs; i++)
            SW.addRequest(RG.generateRequest());
        SW.increment();
    }

    SW.printSummary();

    return 0;
}