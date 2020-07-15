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
    if(file.getFileExtension().compareIgnoreCase(".mp3") == 0)
    {
        std::unique_ptr<TagLib::MPEG::File> mpegFile = std::make_unique<TagLib::MPEG::File>(file.getFullPathName().toRawUTF8());
        
        if(mpegFile->hasID3v2Tag())
        {
            return std::make_unique<ID3v2MetadataReader>(std::move(mpegFile));
        }
        
        else if(mpegFile->hasID3v1Tag())
        {
            return std::make_unique<TagLibTagReader>(std::move(mpegFile));
        }
    }
    
    else if(file.getFileExtension().compareIgnoreCase(".wav") == 0)
    {
        std::unique_ptr<TagLib::RIFF::WAV::File> wavFile = std::make_unique<TagLib::RIFF::WAV::File>(file.getFullPathName().toRawUTF8());
        
        if(wavFile->hasID3v2Tag())
        {
            return std::make_unique<ID3v2MetadataReader>(std::move(wavFile));
        }
    }
    
    else if(file.getFileExtension().compareIgnoreCase(".flac") == 0)
    {
        std::unique_ptr<TagLib::FLAC::File> flacFile = std::make_unique<TagLib::FLAC::File>(file.getFullPathName().toRawUTF8());
        
        if(flacFile->hasID3v2Tag())
        {
            return std::make_unique<ID3v2MetadataReader>(std::move(flacFile));
        }
        
        else if(flacFile->hasID3v1Tag())
        {
            return std::make_unique<TagLibTagReader>(std::move(flacFile));
        }
    }
    
    else if(file.getFileExtension().compareIgnoreCase(".mod") == 0 || file.getFileExtension().compareIgnoreCase(".s3m") == 0 || file.getFileExtension().compareIgnoreCase(".xm") == 0)
    {
        std::unique_ptr<TagLib::File> modFile = std::make_unique<TagLib::File>(file.getFullPathName().toRawUTF8());
        
        return std::make_unique<TagLibTagReader>(std::move(modFile));
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

