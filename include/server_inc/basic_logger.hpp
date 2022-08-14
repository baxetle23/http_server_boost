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
    inline static LogPriority verbosity;
    inline static std::string filepath;
    inline static std::mutex  mutex_logger;

public:
    static void setFilePath(const std::string& file_path);
    static void setVerbosity(LogPriority new_priority);
    static void Log(LogPriority priority, const std::string& message);

};

} //namespace server
} //namespace http

//add time message 
//add multy templates parametrs
//add root for log file from cmake ..