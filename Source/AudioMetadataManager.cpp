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
    formatManager.registerBasicFormats();
}

AudioMetadataManager::~AudioMetadataManager()
{
    
}

std::unique_ptr<AudioMetadataReader> AudioMetadataManager::createMetadataReader(const File& file)
{
    if(file.getFileExtension().compare(".mp3") == 0)
    {
        TagLib::MPEG::File* mpegFile = new TagLib::MPEG::File(file.getFullPathName().toRawUTF8());
        
        if(mpegFile->hasID3v2Tag())
        {
            std::unique_ptr<ID3v2MetadataReader> ptr = std::make_unique<ID3v2MetadataReader>(mpegFile);
            return ptr;
        }
    }
    
    /*TagLib::FileRef tFile(file.getFullPathName().toUTF8(), false);
    
    //Taglib type metadata reader
    if(!tFile.tag()->isEmpty())
    {
        std::unique_ptr<TagLibTagReader> ptr = std::make_unique<TagLibTagReader>(file);
        return ptr;
    }*/
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

