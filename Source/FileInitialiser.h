/*
  ==============================================================================

    FileInitializer.h
    Created: 22 Jun 2020 4:54:12pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioMetadataManager.h"

class Mediator;

class FileInitialiser
{
public:
    FileInitialiser();
    ~FileInitialiser();
    
    //Returns false if error when choosing or empty folder chosen
    bool lookForNewFiles();
    
    std::vector<std::unique_ptr<AudioMetadataReader>>& getResult();
    
private:
    File decompressZipToLocation(const File& zip);
    
    void clearCurrentFiles();
    
    bool hasOwnership;
    
    AudioMetadataManager metadataManager;
    
    std::vector<std::unique_ptr<AudioMetadataReader>> currentFiles;
};
