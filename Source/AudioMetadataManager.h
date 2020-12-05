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
#include "AudioMetadataWildcardManager.h"
#include "mpegfile.h"
#include "wavfile.h"
#include "flacfile.h"
#include "modfile.h"
#include "aifffile.h"
#include "trueaudiofile.h"
#include "wavpackfile.h"

#include "../JuceLibraryCode/JuceHeader.h"

class AudioMetadataManager
{
public:
    AudioMetadataManager();
    ~AudioMetadataManager();
    
    std::unique_ptr<AudioMetadataReader> createMetadataReader(const File& file);
    
    bool moveFileBasedOnWildcardPath(AudioMetadataReader* fileToMove, const String& newLocationWithWildcards);
    
private:
    
    AudioMetadataWildcardManager wildcardInterpretter;
};
