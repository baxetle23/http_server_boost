#pragma once

#include <fstream>
#include <string>
#include <mutex>

namespace http {
namespace server {

enum LogPriority {
    TraceP, 
    DebugP, 
    InfoP, 
    WarnP, 
    ErrorP, 
    FatalP
};


class BasicLogger {
private:
    static inline LogPriority verbosity {LogPriority::TraceP};
    static inline std::string filepath  {"log_server.txt"};

public:
    static void setFilePath(const std::string& file_path);
    static void setVerbosity(LogPriority new_priority);
    static void Log(LogPriority priority, const std::string& message);

};

} //namespace server
} //namespace http

//task:
//add time message 
//add multy templates parametrs
//add root for log file from cmake ..