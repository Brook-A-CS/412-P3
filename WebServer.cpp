#include <iostream>
#include "WebServer.h"
#include "Color.h"


void WebServer::processRequest(Request&& R) {
    if (timeLeft != 0) {
        std::cout << Color::YELLOW << "[WARNING]: " << Color::RESET 
                << "Server replacing unfinished Request" << std::endl; 
    }

    Req = R;
    timeLeft = R.getTime();
}

void WebServer::tick() {
    if (timeLeft > 0) timeLeft--;
}