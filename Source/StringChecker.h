/*
  ==============================================================================

    StringChecker.h
    Created: 22 Mar 2020 8:15:22pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class StringChecker
{
public:
    StringChecker();
    ~StringChecker();
    
    static String removeNumbers(String inputString);
    static String removeCharacters(String inputString, bool capitals);
    static String removeSymbols(String inputString);
    static String capatalizeFirstLetters(String inputString);
    static String decapatalizeWords(String inputString);
    
private:
    
};
