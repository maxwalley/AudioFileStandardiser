/*
  ==============================================================================

    FormatMetadataManager.h
    Created: 27 May 2020 6:12:50pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "FormatMetadataReader.h"
#include "TagLibTagReader.h"
#include "fileref.h"

#include "../JuceLibraryCode/JuceHeader.h"

class FormatMetadataManager
{
public:
    FormatMetadataManager();
    ~FormatMetadataManager();
    
    std::unique_ptr<FormatMetadataReader> createMetadataReader(File& file);
    
private:
    
    AudioFormatManager formatManager;
    
};
