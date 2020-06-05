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
#include "FilePathWildcardInterpretter.h"

#include "../JuceLibraryCode/JuceHeader.h"

class FormatMetadataManager
{
public:
    FormatMetadataManager();
    ~FormatMetadataManager();
    
    std::unique_ptr<FormatMetadataReader> createMetadataReader(File& file);
    
    bool moveFileBasedOnWildcardPath(FormatMetadataReader* fileToMove, String newLocationWithWildcards);
    
    void testOutput(String inputstr, FormatMetadataReader* input);
    
private:
    
    AudioFormatManager formatManager;
    FilePathWildcardInterpretter wildcardInterpretter;
    
};
