#pragma once
#include <string>


class Request {
    private:
        std::string ipIn;
        std::string ipOut;
        int time;
        char jobType;

    public:
        Request(std::string in,std::string out, int time, char job) : ipIn(in), ipOut(out), time(time), jobType(job) {};
        std::string getIPIn() const { return ipIn; };
        std::string getIpOut() const { return ipOut; };
        int getTime() const { return time; }; 
        char getJob() const { return jobType; }; 
};
