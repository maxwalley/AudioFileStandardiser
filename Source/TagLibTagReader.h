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
#include "tag.h"

class TagLibTagReader : public AudioMetadataReader
{
public:
    TagLibTagReader(std::unique_ptr<TagLib::File> file);
    TagLibTagReader(const TagLib::FileRef& file);
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
    
protected:
    std::unique_ptr<TagLib::File> metadataFile;
    TagLib::Tag* metadata;
    
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TagLibTagReader)
};
