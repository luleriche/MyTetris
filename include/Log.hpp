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
    
    template<class T>
    static void debug(T msg){
        if(logLevel <= INFO)
            std::cout << "\033[36m" << "[DEBUG] " << msg << "\033[0m" << std::endl;
    }
    
    template<class T>
    static void info(T msg){
        if(logLevel <= INFO)
            std::cout << "\033[32m" << "[INFO] " << msg << "\033[0m" << std::endl;
    }
    
    template<class T>
    static void warn(T msg){
        if(logLevel <= INFO)
            std::cout << "\033[33m" << "[WARN] " << msg << "\033[0m" << std::endl;
    }

    template<class T>
    static void error(T msg){
        if(logLevel <= INFO)
            std::cout << "\033[31m" << "[ERROR] " << msg << "\033[0m" << std::endl;
    }
};