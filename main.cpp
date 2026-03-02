#include <iostream>
#include <fstream>
#include <random>
#include "LoadBalancer.h"
#include "RequestGenerator.h"
#include "Logger.h"

int main() {

    // Config defaults
    int totalTime = 10000;
    int numServers = 10;
    float reqChance = 0.10f;
    std::string logFile = "loadbalancer.log";
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
        if (key == "TOTAL_TIME") totalTime = std::stoi(val);
        else if (key == "NUM_SERVERS") numServers = std::stoi(val);
        else if (key == "REQUEST_CHANCE") reqChance = std::stof(val);
        else if (key == "LOG_FILE") logFile = val;
        else if (key == "BLOCKED_RANGE") blockedRange = val;
    }

    Logger::get().open(logFile);
    Logger::get().info("Config: total_time=" + std::to_string(totalTime)
        + " servers=" + std::to_string(numServers)
        + " req_chance=" + std::to_string(reqChance));

    LoadBalancer LB(numServers);
    LB.blockIP(blockedRange);
    RequestGenerator RG;

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> chanceDist(0.0f, 1.0f);

    for (int t = 0; t < totalTime; t++) {
        int numReqs = (int)reqChance;
        if (chanceDist(gen) < (reqChance - numReqs)) numReqs++;
        for (int i = 0; i < numReqs; i++)
            LB.addRequest(RG.generateRequest());
        LB.increment();
    }

    LB.printSummary();

    return 0;
}