#pragma once
#include <string>
#include <fstream>

class Logger {
    private:
        std::ofstream logFile;
        int tick = 0;

        std::string tickStr() const;
        void toFile(const std::string& tag, const std::string& msg);

    public:
        static Logger& get();

        void open(const std::string& filename);
        void setTick(int t) { tick = t; }

        void detail(const std::string& msg); 
        void info(const std::string& msg); // cyan
        void warn(const std::string& msg); // yellow
        void alert(const std::string& msg); // red
        void summary(const std::string& msg); // blue
};
