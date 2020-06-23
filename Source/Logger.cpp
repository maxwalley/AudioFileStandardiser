/*
  ==============================================================================

    Logger.cpp
    Created: 23 Jun 2020 12:32:16pm
    Author:  Max Walley

  ==============================================================================
*/

#include "Logger.h"

std::ofstream LoggerC::logFile;

std::string LoggerC::timeFormat = "%T";

LoggerC::LoggerC()  :   timeSet(false)
{
    
}

LoggerC::~LoggerC()
{
    if(logFile.is_open())
    {
        logFile.close();
    }
}

bool LoggerC::logMessage(std::string message, bool logTime)
{
    if(logFile.is_open())
    {
        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        
        std::time_t time = std::chrono::system_clock::to_time_t(start);
        
        logFile << std::put_time(std::localtime(&time), timeFormat.c_str()) << " - " << message << std::endl;
        
        return true;
    }
    return false;
}

bool LoggerC::setLogFile(std::string filePath)
{
    if(logFile.is_open())
    {
        logFile.close();
    }
    
    logFile.open(filePath, std::ios::out | std::ios::trunc);
    
    if(logFile.is_open())
    {
        return true;
    }
    return false;
}

void LoggerC::startTimer()
{
    startTimePoint = std::chrono::steady_clock::now();
    timeSet = true;
}

void LoggerC::setTimeFormat(std::string newTimeFormat)
{
    timeFormat = newTimeFormat;
}
