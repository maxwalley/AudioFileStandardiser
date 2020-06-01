/*
  ==============================================================================

    StringChecker.cpp
    Created: 22 Mar 2020 8:15:22pm
    Author:  Max Walley

  ==============================================================================
*/

#include "StringChecker.h"

StringChecker::StringChecker()
{
    
}

StringChecker::~StringChecker()
{
    
}

String StringChecker::removeNumbers(String inputString)
{
    return inputString.removeCharacters("0123456789");
}

String StringChecker::removeCharacters(String inputString, bool capitals = false)
{
    if(capitals == false)
    {
        return inputString.removeCharacters("abcdefghijklmnopqrstuvwxyz");
    }
    
    return inputString.removeCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

String StringChecker::removeSymbols(String inputString)
{
    
    for(int i = 0; i < inputString.length(); i++)
    {
        if((inputString.getCharPointer() + i).isLetterOrDigit() == false && (inputString.getCharPointer()[i] != *(" ")))
        {
            inputString = inputString.replaceSection(i, 1, "");
            i--;
        }
    }
    return inputString;
}

String StringChecker::capatalizeFirstLetters(String inputString)
{
    for(int i = 0; i < inputString.length(); i++)
    {
        if(i == 0)
        {
            if(inputString.getCharPointer().isLowerCase() == true)
            {
                String newChar = inputString.substring(0, 1).toUpperCase();
                inputString = inputString.replaceSection(0, 1, newChar);
            }
        }
        
        if(inputString.getCharPointer()[i - 1] == *(" "))
        {
            if((inputString.getCharPointer() + i).isLowerCase() == true)
            {
                String newChar = inputString.substring(i, i + 1).toUpperCase();
                inputString = inputString.replaceSection(i, 1, newChar);
            }
        }
    }
    
    return inputString;
}

String StringChecker::decapatalizeWords(String inputString)
{
    inputString = inputString.replace(" A ", " a ");
    inputString = inputString.replace(" An ", " an ");
    inputString = inputString.replace(" The ", " the ");
    inputString = inputString.replace(" And ", " and ");
    inputString = inputString.replace(" For ", " for ");
    inputString = inputString.replace(" Nor ", " nor ");
    inputString = inputString.replace(" But ", " but ");
    inputString = inputString.replace(" Or ", " or ");
    inputString = inputString.replace(" At ", " at ");
    inputString = inputString.replace(" By ", " by ");
    inputString = inputString.replace(" In ", " in ");
    inputString = inputString.replace(" Of ", " of ");
    inputString = inputString.replace(" On ", " on ");
    inputString = inputString.replace(" To ", " to ");
    
    return inputString;
}
