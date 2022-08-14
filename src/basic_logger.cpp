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
        std::scoped_lock guard(mutex_logger);
        std::ofstream FILE(filepath, std::ios_base::app);
        switch (priority) {
            case TraceP: FILE << "Trace:\t"; break;
            case DebugP: FILE << "Debug:\t"; break;
            case InfoP: FILE << "Info:\t"; break;
            case WarnP: FILE << "Warn:\t"; break;
            case ErrorP: FILE << "Error:\t"; break;
        }
        FILE << message << "\n";
        FILE.close();
    }
}

} //namespace server
} //namespace http
