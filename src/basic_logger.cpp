#include "basic_logger.hpp"

namespace http {
namespace server {

void BasicLogger::setFilePath(const std::string& file_path) {
    filepath = file_path;
}

void BasicLogger::setVerbosity(LogPriority new_priority) {
    verbosity = new_priority;
}

void BasicLogger::Log(LogPriority priority, const std::string& message) {
    if (priority >= verbosity) {
        std::ofstream FILE(filepath, std::ios_base::app);
        switch (priority) {
            case TraceP: {
                FILE << "[Trace] : "; 
                break;
            } case DebugP: {
                FILE << "[Debug] : "; 
                break;
            } case InfoP: {
                FILE << "[Info] : "; 
                break;
            } case WarnP: {
                FILE << "[Warn] : "; 
                break;
            } case ErrorP: {
                FILE << "[Error] : "; 
                break;
            } case FatalP: {
                FILE << "[Fatal] : ";
            }
        }
        FILE << message << std::endl;
        FILE.close();
    }
}

} //namespace server
} //namespace http
