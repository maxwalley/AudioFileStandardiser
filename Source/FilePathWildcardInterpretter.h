/*
  ==============================================================================

    FilePathWildcardInterpretter.h
    Created: 5 Jun 2020 4:54:11pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once
#include "AudioMetadataReader.h"

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
    
    String interpretString(const String& input, AudioMetadataReader* file);
    
    StringArray getCompatibleWildcards() const;
    
private:
    StringArray compatibleWildcards;
    trackNumFormat currentTrackNumFormat;
    
};
