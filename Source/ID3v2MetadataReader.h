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

class ID3v2MetadataReader   :   public TagLibTagReader
{
public:
    ID3v2MetadataReader(const File& inputFile, TagLib::File* file, TagLib::ID3v2::Tag* tag);
    ~ID3v2MetadataReader();
    
private:
    
    TagLib::ID3v2::Tag* metadataTag;
    //TagLib::File* metadataFile;
    
};
