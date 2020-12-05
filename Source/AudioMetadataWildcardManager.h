/*
  ==============================================================================

    FilePathWildcardInterpretter.h
    Created: 5 Jun 2020 4:54:11pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "WildcardManager.h"
#include "AudioMetadataReader.h"

/*class AudioMetadataWildcardManager
{
public:
    enum trackNumFormat
    {
        minimumSingleDigit = 0,
        minimumDoubleDigit = 1,
        minimumTripleDigit = 2
    };
    
    AudioMetadataWildcardManager();
    ~AudioMetadataWildcardManager();
    
    void setTrackNumFormat();
    
    String interpretString(const String& input, AudioMetadataReader* file);
    
    StringArray getCompatibleWildcards() const;
    
private:
    StringArray compatibleWildcards;
    trackNumFormat currentTrackNumFormat;
    
};*/


class AudioMetadataWildcardManager  : public WildcardManager<AudioMetadataReader*>
{
public:
    enum trackNumFormat
    {
        minimumSingleDigit = 0,
        minimumDoubleDigit = 1,
        minimumTripleDigit = 2
    };
    
    AudioMetadataWildcardManager()  : compatibleWildcards({"$artist", "$album", "$tracknum", "$title", "$year", "$fileformat"}) {};
    
    virtual ~AudioMetadataWildcardManager(){};
    
    String convertWildcardToString (AudioMetadataReader* data, const String& stringToRead) const override;
    
    StringArray getCompatibleWildcards() const override;
    
    void setTrackNumFormat(trackNumFormat newFormat);
    
private:
    StringArray compatibleWildcards;
    trackNumFormat currentTrackNumFormat = minimumDoubleDigit;
};
