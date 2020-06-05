/*
  ==============================================================================

    FormatMetadataManager.cpp
    Created: 27 May 2020 6:12:50pm
    Author:  Max Walley

  ==============================================================================
*/

#include "FormatMetadataManager.h"

FormatMetadataManager::FormatMetadataManager()
{
    formatManager.registerBasicFormats();
}

FormatMetadataManager::~FormatMetadataManager()
{
    
}

std::unique_ptr<FormatMetadataReader> FormatMetadataManager::createMetadataReader(File& file)
{
    AudioFormatManager manager;
    manager.registerBasicFormats();
    
    TagLib::FileRef tFile(file.getFullPathName().toUTF8(), false);
            
    if(!tFile.tag()->isEmpty())
    {
        std::unique_ptr<TagLibTagReader> ptr = std::make_unique<TagLibTagReader>(file);
        return ptr;
    }
    return nullptr;
}

bool moveFileBasedOnWildcardPath(FormatMetadataReader* fileToMove, String newLocationWithWildcards)
{
    
}

void FormatMetadataManager::testOutput(String inputstr, FormatMetadataReader* input)
{
    DBG(wildcardInterpretter.interpretString(inputstr, input));
}
