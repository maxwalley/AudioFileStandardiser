/*
  ==============================================================================

    FileInitializer.h
    Created: 22 Jun 2020 4:54:12pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Mediator.h"
#include "AudioMetadataManager.h"

class FileInitialiser
{
public:
    FileInitialiser();
    ~FileInitialiser();
    
    bool lookForNewFiles();
    
    std::vector<AudioMetadataReader*> getResult();
    
private:
    File decompressZipToLocation(const File& zip);
    
    void clearCurrentFiles();
    
    Mediator* mediator;
    AudioMetadataManager metadataManager;
    
    std::vector<AudioMetadataReader*> currentFiles;
};
