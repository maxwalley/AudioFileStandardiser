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
        DBG("Tag Lib Compatable File");
        std::unique_ptr<TagLibTagReader> ptr = std::make_unique<TagLibTagReader>(file);
        return ptr;
    }
    return nullptr;
}
