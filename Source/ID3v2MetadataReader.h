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
    ID3v2MetadataReader(TagLib::File* file);
    ~ID3v2MetadataReader();
    
private:
    
    TagLib::ID3v2::Tag* metadataTag;
    //TagLib::File* metadataFile;
    
    //Function that will find the ID3v2 tag in a file. If none exists it will return nullptr
    TagLib::ID3v2::Tag* findTag(TagLib::File* inputFile);
    
};
