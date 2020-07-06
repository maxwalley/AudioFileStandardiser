/*
  ==============================================================================

    AudioMetadataManager.h
    Created: 27 May 2020 6:12:50pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "ID3v2MetadataReader.h"
#include "fileref.h"
#include "FilePathWildcardInterpretter.h"
#include "mpegfile.h"
#include "fileref.h"

#include "../JuceLibraryCode/JuceHeader.h"

class AudioMetadataManager
{
public:
    AudioMetadataManager();
    ~AudioMetadataManager();
    
    std::unique_ptr<AudioMetadataReader> createMetadataReader(const File& file);
    
    bool moveFileBasedOnWildcardPath(AudioMetadataReader* fileToMove, const String& newLocationWithWildcards);
    
private:
    
    AudioFormatManager formatManager;
    FilePathWildcardInterpretter wildcardInterpretter;
};
