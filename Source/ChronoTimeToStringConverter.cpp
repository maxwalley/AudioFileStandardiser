/*
  ==============================================================================

    ChronoTimeToStringConverter.cpp
    Created: 16 Jul 2020 12:33:36pm
    Author:  Max Walley

  ==============================================================================
*/

#include "ChronoTimeToStringConverter.h"
#include <iostream>

ChronoTimeToStringConverter::ChronoTimeToStringConverter()
{
    
}

ChronoTimeToStringConverter::~ChronoTimeToStringConverter()
{
    
}

std::string ChronoTimeToStringConverter::convertToWildcardString(const std::string& wildcardString, std::chrono::duration<int> time)
{
    std::string outputString = wildcardString;
    
    std::string::size_type hoursStringPos = outputString.find("%h");
    
    if(hoursStringPos != std::string::npos)
    {
        std::chrono::duration<int, std::ratio<3600>> timeInHours = std::chrono::floor<std::chrono::duration<int, std::ratio<3600>>>(time);
        
        outputString.erase(hoursStringPos, 2);
        
        outputString.insert(hoursStringPos, std::to_string(timeInHours.count()));
        
        if(timeInHours.count() < 10)
        {
            outputString.insert(hoursStringPos, "0");
        }
        
        time -= timeInHours;
    }
    
    std::string::size_type minutesStringPos = outputString.find("%m");
    
    if(minutesStringPos != std::string::npos)
    {
        std::chrono::duration<int, std::ratio<60>> timeInMinutes = std::chrono::floor<std::chrono::duration<int, std::ratio<60>>>(time);
        
        outputString.erase(minutesStringPos, 2);
        
        outputString.insert(minutesStringPos, std::to_string(timeInMinutes.count()));
        
        if(timeInMinutes.count() < 10)
        {
            outputString.insert(minutesStringPos, "0");
        }
        
        time -= timeInMinutes;
    }
    
    std::string::size_type secondsStringPos = outputString.find("%s");
    
    if(secondsStringPos != std::string::npos)
    {
        outputString.erase(secondsStringPos, 2);
        
        outputString.insert(secondsStringPos, std::to_string(time.count()));
        
        if(time.count() < 10)
        {
            outputString.insert(secondsStringPos, "0");
        }
    }
    
    return outputString;
}
