/*
  ==============================================================================

    FilePathWildcardInterpretter.h
    Created: 5 Jun 2020 4:54:11pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once
#include "FormatMetadataReader.h"

class FilePathWildcardInterpretter
{
public:
    enum trackNumFormat
    {
        minimumSingleDigit = 0,
        minimumDoubleDigit = 1,
        minimumTripleDigit = 2
    };
    
    FilePathWildcardInterpretter();
    ~FilePathWildcardInterpretter();
    
    void setTrackNumFormat();
    
    String interpretString(String input, FormatMetadataReader* file);
    
    StringArray getCompatibleWildcards() const;
    
private:
    StringArray compatibleWildcards;
    trackNumFormat currentTrackNumFormat;
    
};
