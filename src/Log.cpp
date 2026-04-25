#include "Log.hpp"
#include <iostream>

Log::Level Log::logLevel = Log::DEBUG;

void Log::setLogLevel(Level newLogLevel){
    Log::logLevel = newLogLevel;
}