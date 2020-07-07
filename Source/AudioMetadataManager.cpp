/*
  ==============================================================================

    AudioMetadataManager.cpp
    Created: 27 May 2020 6:12:50pm
    Author:  Max Walley

  ==============================================================================
*/

#include "AudioMetadataManager.h"

AudioMetadataManager::AudioMetadataManager()
{
    
}

AudioMetadataManager::~AudioMetadataManager()
{
    
}

std::unique_ptr<AudioMetadataReader> AudioMetadataManager::createMetadataReader(const File& file)
{
    if(file.getFileExtension().compare(".mp3") == 0)
    {
        std::unique_ptr<TagLib::MPEG::File> mpegFile = std::make_unique<TagLib::MPEG::File>(file.getFullPathName().toRawUTF8());
        
        std::unique_ptr<ID3v2MetadataReader> ptr = std::make_unique<ID3v2MetadataReader>(std::move(mpegFile));
        
        if(ptr)
        {
            return ptr;
        }
    }
    
    return nullptr;
}

bool AudioMetadataManager::moveFileBasedOnWildcardPath(AudioMetadataReader* fileToMove, const String& newLocationWithWildcards)
{
    String convertedLocation = wildcardInterpretter.interpretString(newLocationWithWildcards, fileToMove);
    
    if(!File(convertedLocation).exists())
    {
        File(convertedLocation).createDirectory();
    }
    
    fileToMove->moveFileToNewDirectory(convertedLocation);
}

