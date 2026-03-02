#pragma once

#include <optional>
#include "Request.h"

/// @brief Simulates a single web server that processes one Request at a time.
class WebServer {
    private:
        std::optional<Request> Req;
        int timeLeft;

    public:
        /// @brief Constructs an idle WebServer.
        WebServer() : timeLeft(0) {};

        /// @brief Constructs a WebServer immediately processing a request.
        WebServer(const Request& R) : Req(R), timeLeft{R.getTime()} {};

        /// @brief Returns true if the server has no active request.
        bool isFree() { return timeLeft == 0; }

        /// @brief Assigns a new request to this server and begins processing.
        /// @param R The request to process
        void processRequest(Request&& R);

        /// @brief Advances the server by one clock cycle, decrementing time remaining.
        void tick();
};
