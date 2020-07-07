/*
  ==============================================================================

    MetadataReader.h
    Created: 7 Jul 2020 10:16:56am
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MetadataReader
{
public:
    MetadataReader(const File& inputFile);
    virtual ~MetadataReader();
    
    enum class MetadataType
    {
        ID3v2
    };
    
    virtual MetadataType getMetadataType() = 0;
    
    virtual void moveFileToNewDirectory(const String& newLocation);
    virtual void changeFileName(const String& newName);
    virtual File& getFile();
    
protected:
    File fileToRead;
    
};
