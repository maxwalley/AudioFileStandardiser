/*
  ==============================================================================

    ID3MetadataReader.h
    Created: 27 May 2020 6:37:30pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "FormatMetadataReader.h"

class ID3MetadataReader : public FormatMetadataReader
{
public:
    ID3MetadataReader(File* input);
    ~ID3MetadataReader();
    
    int getTrackNum() override;
    String getTrackTitle() override;
    String getArtistName() override;
    String getAlbumName() override;
    int getYear() override;
    
    void setTrackNum(int newTrackNum) override;
    void setTrackTitle(String newTrackTitle) override;
    void setArtistName(String newArtistName) override;
    void setAlbumName(String newAlbumName) override;
    void setYear(String newYear) override;
    
private:
    
};
