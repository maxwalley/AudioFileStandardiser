/*
  ==============================================================================

    AudioMetadataReader.cpp
    Created: 7 Jun 2020 3:02:17pm
    Author:  Max Walley

  ==============================================================================
*/

#include "AudioMetadataReader.h"

AudioMetadataReader::AudioMetadataReader(const File& inputFile) :   fileToRead(inputFile)
{
    
}

AudioMetadataReader::~AudioMetadataReader()
{
    
}

void AudioMetadataReader::moveFileToNewDirectory(const String& newLocation)
{
    String locationToMoveTo = newLocation + "/" + fileToRead.getFileName();
    fileToRead.moveFileTo(File(locationToMoveTo));
    fileToRead = locationToMoveTo;
}

void AudioMetadataReader::changeFileName(const String& newName)
{
    String newPath = fileToRead.getFullPathName().replace(fileToRead.getFileNameWithoutExtension(), newName);
    fileToRead.moveFileTo(File(newPath));
    fileToRead = newPath;
}

File& AudioMetadataReader::getFile()
{
    return fileToRead;
}
