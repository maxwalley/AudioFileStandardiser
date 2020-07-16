/*
  ==============================================================================

    ChronoTimeToStringConverter.h
    Created: 16 Jul 2020 12:33:36pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include <chrono>
#include <string>

class ChronoTimeToStringConverter
{
public:
    ChronoTimeToStringConverter();
    ~ChronoTimeToStringConverter();
    
    static std::string convertToWildcardString(const std::string& wildcardString, std::chrono::duration<int> time);
    
private:
    
};
