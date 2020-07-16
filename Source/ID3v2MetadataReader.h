/*
  ==============================================================================

    ID3v2MetadataReader.h
    Created: 3 Jul 2020 11:06:40am
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TagLibTagReader.h"
#include "id3v2tag.h"
#include "tlist.h"
#include "id3v2frame.h"
#include "mpegfile.h"

class ID3v2MetadataReader   :   public TagLibTagReader
{
public:
    ID3v2MetadataReader(std::unique_ptr<TagLib::File> file, TagLib::ID3v2::Tag* associatedTag);
    
    ~ID3v2MetadataReader();
    
    MetadataType getMetadataType() const override;
    
    Image* getArtwork() override;
    
private:
    
    TagLib::ID3v2::Tag* metadataTag;
    
    Image coverArt;
    
    Image extractImage(TagLib::ID3v2::Tag* metadata);
    
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ID3v2MetadataReader)
};
