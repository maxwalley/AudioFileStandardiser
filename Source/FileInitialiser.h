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
    FileInitialiser(const StringArray& supportedFileTypes = StringArray());
    ~FileInitialiser();
    
    //Returns false if error when choosing or empty folder chosen
    bool lookForNewFilesAndAdd();
    
    bool addNewFiles(const Array<File>& files);
    
    std::vector<std::unique_ptr<AudioMetadataReader>>& getResult();
    
    void clearCurrentFiles();
    
    StringArray getSupportedFileTypes() const;
    
    //Set relative zip decomressLocation
    
private:
    std::optional<File> decompressZipToLocation(const File& zip);
    
    AudioMetadataManager metadataManager;
    
    std::vector<std::unique_ptr<AudioMetadataReader>> currentFiles;
    
    String convertSupportedTypesToString();
    
    StringArray supportedTypes;
    
    String supportedTypesInOne;
};
