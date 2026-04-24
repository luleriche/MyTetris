#include "Log.hpp"
#include <iostream>

Log::Level Log::logLevel = Log::INFO;

void Log::setLogLevel(Level newLogLevel){
    logLevel = newLogLevel;
}

void Log::debug(std::string msg){
    if(logLevel <= DEBUG)
        std::cout << "[DEBUG] " << msg << std::endl;
}

void Log::info(std::string msg){
    if(logLevel <= INFO)
        std::cout << "[INFO] " << msg << std::endl;
}

void Log::warn(std::string msg){
    if(logLevel <= WARN)
        std::cout << "[WARN] " << msg << std::endl;
}

void Log::error(std::string msg){
    if(logLevel <= ERROR)
        std::cout << "[ERROR] " << msg << std::endl;
}
