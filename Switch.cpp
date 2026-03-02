#include "Switch.h"
#include "Logger.h"

Switch::Switch(int streamServers, int processServers)
    : streamLB(streamServers, "Stream"), processLB(processServers, "Process") {}

void Switch::addRequest(Request r) {
    if (r.getJob() == 'S') {
        Logger::get().detail("Switch -> Stream : " + r.getIPIn());
        streamLB.addRequest(r);
    } else {
        Logger::get().detail("Switch -> Process: " + r.getIPIn());
        processLB.addRequest(r);
    }
}

void Switch::increment() {
    streamLB.increment();
    processLB.increment();
}

void Switch::blockIP(const std::string& prefix) {
    streamLB.blockIP(prefix);
    processLB.blockIP(prefix);
}

void Switch::printSummary() const {
    streamLB.printSummary();
    processLB.printSummary();
}
