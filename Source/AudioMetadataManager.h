/*
  ==============================================================================

    AudioMetadataManager.h
    Created: 27 May 2020 6:12:50pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "AudioMetadataReader.h"
#include "TagLibTagReader.h"
#include "fileref.h"
#include "FilePathWildcardInterpretter.h"

#include "../JuceLibraryCode/JuceHeader.h"

class AudioMetadataManager
{
public:
    AudioMetadataManager();
    ~AudioMetadataManager();
    
    std::unique_ptr<AudioMetadataReader> createMetadataReader(File& file);
    
    bool moveFileBasedOnWildcardPath(AudioMetadataReader* fileToMove, String newLocationWithWildcards);
    
private:
    
    AudioFormatManager formatManager;
    FilePathWildcardInterpretter wildcardInterpretter;
};

//TO DO
//Abstract this out to metadataManager
//Rename this to audioMetadataManager

//rename AudioMetadataReader to audioMetadataReader
//Follows library pattern found at: https://sourcemaking.com/design_patterns/factory_method/cpp/2
