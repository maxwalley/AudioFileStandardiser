/*
  ==============================================================================

    TagLibTagReader.h
    Created: 27 May 2020 6:37:30pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "AudioMetadataReader.h"
#include "fileref.h"

class TagLibTagReader : public AudioMetadataReader
{
public:
    TagLibTagReader(const File& input);
    ~TagLibTagReader();
    
    int getTrackNum() override;
    String getTrackTitle() override;
    String getArtistName() override;
    String getAlbumName() override;
    int getYear() override;
    
    void setTrackNum(int newTrackNum) override;
    void setTrackTitle(const String& newTrackTitle) override;
    void setArtistName(const String& newArtistName) override;
    void setAlbumName(const String& newAlbumName) override;
    void setYear(int newYear) override;
    
private:
    TagLib::FileRef metadataFile;
    TagLib::Tag* metadata;
    
};
