/*
  ==============================================================================

    AudioMetadataReader.h
    Created: 27 May 2020 6:11:08pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class AudioMetadataReader
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
    
    virtual void moveFileToNewDirectory(const String& newLocation);
    virtual void changeFileName(const String& newName);
    virtual File& getFile();
    
protected:
    File fileToRead;
    
private:
    
};
