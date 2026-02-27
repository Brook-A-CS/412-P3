#pragma once

#include <optional>
#include "Request.h"



class WebServer {
    private:
        std::optional<Request> Req;
        int timeLeft;
    public:
        WebServer() : timeLeft(0)  {};
        WebServer(const Request& R) : Req(R), timeLeft{R.getTime()} {};
        bool isFree() { return timeLeft == 0; }
        void processRequest(Request&& R);  
        void tick();
};