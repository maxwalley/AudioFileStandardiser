/*
  ==============================================================================

    AudioMetadataReader.cpp
    Created: 7 Jun 2020 3:02:17pm
    Author:  Max Walley

  ==============================================================================
*/

#include "AudioMetadataReader.h"

AudioMetadataReader::AudioMetadataReader(File& inputFile) :   fileToRead(inputFile)
{
    
}

AudioMetadataReader::~AudioMetadataReader()
{
    
}

void AudioMetadataReader::moveFileToNewDirectory(String newLocation)
{
    newLocation = newLocation + "/" + fileToRead.getFileName();
    fileToRead.moveFileTo(File(newLocation));
    fileToRead = newLocation;
}

void AudioMetadataReader::changeFileName(String newName)
{
    String newPath = fileToRead.getFullPathName().replace(fileToRead.getFileNameWithoutExtension(), newName);
    fileToRead.moveFileTo(File(newPath));
    fileToRead = newPath;
}

File& AudioMetadataReader::getFile()
{
    return fileToRead;
}
