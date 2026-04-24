#pragma once

#include <iostream>

class Log
{
public:
    enum Level{
        DEBUG = 0, INFO, WARN, ERROR
    };
private:
    static Level logLevel;
public:
    static void setLogLevel(Level newLogLevel);

    static void debug(std::string msg);
    static void info(std::string msg);
    static void warn(std::string msg);
    static void error(std::string msg);
};