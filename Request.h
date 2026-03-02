#pragma once
#include <string>

/// @brief Represents a single network request to be processed by a WebServer.
class Request {
    private:
        std::string ipIn;
        std::string ipOut;
        int time;
        char jobType;

    public:
        /// @brief Constructs a Request.
        /// @param in Source IP address
        /// @param out Destination IP address
        /// @param time Processing time in clock cycles
        /// @param job Job type character ('P' or 'S')
        Request(std::string in, std::string out, int time, char job) : ipIn(in), ipOut(out), time(time), jobType(job) {};

        /// @brief Returns the source IP address.
        std::string getIPIn() const { return ipIn; };

        /// @brief Returns the destination IP address.
        std::string getIpOut() const { return ipOut; };

        /// @brief Returns the processing time in clock cycles.
        int getTime() const { return time; };

        /// @brief Returns the job type character.
        char getJob() const { return jobType; };
};
