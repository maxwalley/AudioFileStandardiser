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
    
}

FormatMetadataManager::~FormatMetadataManager()
{
    
}

std::unique_ptr<FormatMetadataReader> FormatMetadataManager::createMetadataReader(File& file)
{
    ID3MetadataReader reader(file);
    
    std::unique_ptr<ID3MetadataReader> ptr = std::make_unique<ID3MetadataReader>(file);
    
    return ptr;
}
