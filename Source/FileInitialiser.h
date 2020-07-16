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
#include "FileAndFolderCreator.h"


class FileInitialiser
{
public:
    FileInitialiser();
    ~FileInitialiser();
    
    //Returns false if error when choosing or empty folder chosen
    bool lookForNewFiles();
    
    std::vector<std::unique_ptr<AudioMetadataReader>>& getResult();
    
    void clearCurrentFiles();
    
private:
    std::optional<File> decompressZipToLocation(const File& zip);
    
    AudioMetadataManager metadataManager;
    
    std::vector<std::unique_ptr<AudioMetadataReader>> currentFiles;
};
