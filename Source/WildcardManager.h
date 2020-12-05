/*
  ==============================================================================

    WildcardManager.h
    Created: 5 Dec 2020 2:39:20pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

template<class T>
class WildcardManager
{
public:
    WildcardManager(){};
    virtual ~WildcardManager(){};

    //This returns a string with wildcards replaced with the correct data
    String interpretString (T data, const String& stringToRead) const
    {
        String convertedString = stringToRead;
        
        StringArray wildcards = getCompatibleWildcards();
        
        for(const String& card : wildcards)
        {
            convertedString = convertedString.replace(card, convertWildcardToString(data, card));
        }
        
        return convertedString;
    };
    
    //This should return a list of all the compatible wildcards
    virtual StringArray getCompatibleWildcards() const = 0;
    
protected:
    
    //This should take a wildcard and return a string based upon it. If the wildcard is not recognised it should return std::nullopt
    virtual String convertWildcardToString (T data, const String& wildcard) const = 0;
};
