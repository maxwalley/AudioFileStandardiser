/*
  ==============================================================================

    AudioMetadataReader.h
    Created: 27 May 2020 6:11:08pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MetadataReader.h"

class AudioMetadataReader   :   public MetadataReader
{
public:
    AudioMetadataReader(const File& inputFile);
    virtual ~AudioMetadataReader();
    
    virtual int getTrackNum() = 0;
    virtual String getTrackTitle() = 0;
    virtual String getArtistName() = 0;
    virtual String getAlbumName() = 0;
    virtual int getYear() = 0;
    
    virtual void setTrackNum(int newTrackNum) = 0;
    virtual void setTrackTitle(const String& newTrackTitle) = 0;
    virtual void setArtistName(const String& newArtistName) = 0;
    virtual void setAlbumName(const String& newAlbumName) = 0;
    virtual void setYear(int newYear) = 0;
    
    virtual int getSampleRate() const = 0;
    virtual int getNumChannels() const = 0;
    virtual std::chrono::seconds getLength() const = 0;
    
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioMetadataReader)
};
