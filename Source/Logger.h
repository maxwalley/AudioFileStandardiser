/*
  ==============================================================================

    Logger.h
    Created: 23 Jun 2020 12:32:16pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include <string>
#include <chrono>
#include <fstream>

class LoggerC
{
public:
    LoggerC(const std::string& logFilePath);
    ~LoggerC();
    
    //returns false if no file is opened
    static bool logMessage(const std::string& message, bool logTime);
    
    //Must be called before logging any messages returns if the file was opened succesfully
    bool setLogFile(const std::string& filePath);
    
    void startTimer();
    
    template <class durationToUse>// this should be of type std::chrono::duration
    durationToUse stopTimer(bool log, const std::string& message = "")
    {
        if(timeSet)
        {
            std::chrono::time_point<std::chrono::steady_clock> endTimePoint = std::chrono::steady_clock::now();
        
            durationToUse duration = std::chrono::duration_cast<durationToUse>(endTimePoint - startTimePoint);
        
            if(log)
            {
                logMessage(message + " " + std::to_string(duration.count()), true);
            }
        
            return duration;
        }
    };
    
    //time format should comply with std::putTime
    static void setTimeFormat(const std::string& newTimeFormat);
    
private:
    
    static std::ofstream logFile;
    
    std::chrono::time_point<std::chrono::steady_clock> startTimePoint;
    
    bool timeSet;
    
    static std::string timeFormat;
};
