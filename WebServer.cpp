#include "WebServer.h"
#include "Logger.h"


void WebServer::processRequest(Request&& R) {
    if (timeLeft != 0) {
        Logger::get().warn("Server replacing unfinished request");
    }

    Req = R;
    timeLeft = R.getTime();
}

void WebServer::tick() {
    if (timeLeft > 0) timeLeft--;
}