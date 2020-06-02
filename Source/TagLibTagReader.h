/*
  ==============================================================================

    TagLibTagReader.h
    Created: 27 May 2020 6:37:30pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "FormatMetadataReader.h"
#include "fileref.h"

class TagLibTagReader : public FormatMetadataReader
{
public:
    TagLibTagReader(File& input);
    ~TagLibTagReader();
    
    int getTrackNum() override;
    String getTrackTitle() override;
    String getArtistName() override;
    String getAlbumName() override;
    int getYear() override;
    
    void setTrackNum(int newTrackNum) override;
    void setTrackTitle(String newTrackTitle) override;
    void setArtistName(String newArtistName) override;
    void setAlbumName(String newAlbumName) override;
    void setYear(int newYear) override;
    
    void moveFile(String newDirectory) override;
    String getFileLocation() override;
    String getFileName() override;
    String getFileNameWithoutExtension() override;
    
private:
    //File fileToRead;
    TagLib::FileRef metadataFile;
    TagLib::Tag* metadata;
    
};
