/*
  ==============================================================================

    FormatMetadataReader.h
    Created: 27 May 2020 6:11:08pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class FormatMetadataReader
{
public:
    FormatMetadataReader(File& inputFile);
    virtual ~FormatMetadataReader();
    
    virtual int getTrackNum() = 0;
    virtual String getTrackTitle() = 0;
    virtual String getArtistName() = 0;
    virtual String getAlbumName() = 0;
    virtual int getYear() = 0;
    
    virtual void setTrackNum(int newTrackNum) = 0;
    virtual void setTrackTitle(String newTrackTitle) = 0;
    virtual void setArtistName(String newArtistName) = 0;
    virtual void setAlbumName(String newAlbumName) = 0;
    virtual void setYear(int newYear) = 0;
    
    virtual void moveFileToNewDirectory(String newLocation);
    virtual void changeFileName(String newName);
    virtual File& getFile();
    
protected:
    File fileToRead;
    
private:
    
};
