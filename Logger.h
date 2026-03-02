#pragma once
#include <string>
#include <fstream>

/// @brief Singleton logger that writes detailed output to a file and important
///        events to the terminal with color coding.
///
/// Log levels:
///  - detail()  -> file only  (every request, dispatch, balance check)
///  - info()    -> cyan terminal + file  (server changes, status snapshots)
///  - warn()    -> yellow terminal + file  (server removal, bad state)
///  - alert()   -> red terminal + file  (firewall rule additions)
///  - summary() -> blue terminal + file  (end-of-run statistics)
class Logger {
    private:
        std::ofstream logFile;
        int tick = 0;

        /// @brief Returns a zero-padded tick string, e.g. "[T=00042]".
        std::string tickStr() const;

        /// @brief Writes a tagged, tick-prefixed line to the log file.
        void toFile(const std::string& tag, const std::string& msg);

    public:
        /// @brief Returns the singleton Logger instance.
        static Logger& get();

        /// @brief Opens the log file for writing.
        /// @param filename Path to the output log file
        void open(const std::string& filename);

        /// @brief Sets the current simulation tick shown in log entries.
        /// @param t Current tick number
        void setTick(int t) { tick = t; }

        /// @brief Logs a detailed message to file only.
        void detail(const std::string& msg);

        /// @brief Logs an informational message to the terminal (cyan) and file.
        void info(const std::string& msg);

        /// @brief Logs a warning to the terminal (yellow) and file.
        void warn(const std::string& msg);

        /// @brief Logs an alert to the terminal (red) and file.
        void alert(const std::string& msg);

        /// @brief Logs a summary message to the terminal (blue) and file.
        void summary(const std::string& msg);
};
