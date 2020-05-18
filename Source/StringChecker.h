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
    
    String removeNumbers(String inputString);
    String removeCharacters(String inputString, bool capitals);
    String removeSymbols(String inputString);
    String capatalizeFirstLetters(String inputString);
    String decapatalizeWords(String inputString);
    
private:
    
};
