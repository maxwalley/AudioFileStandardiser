/*
  ==============================================================================

    MetadataReader.cpp
    Created: 7 Jul 2020 10:16:56am
    Author:  Max Walley

  ==============================================================================
*/

#include "MetadataReader.h"

MetadataReader::MetadataReader(const File& inputFile)   :   fileToRead(inputFile)
{
    
}

MetadataReader::~MetadataReader()
{
    
}

void MetadataReader::moveFileToNewDirectory(const String& newLocation)
{
    String locationToMoveTo = newLocation + "/" + fileToRead.getFileName();
    fileToRead.moveFileTo(File(locationToMoveTo));
    fileToRead = locationToMoveTo;
}

void MetadataReader::changeFileName(const String& newName)
{
    String newPath = fileToRead.getFullPathName().replace(fileToRead.getFileNameWithoutExtension(), newName);
    fileToRead.moveFileTo(File(newPath));
    fileToRead = newPath;
}

File& MetadataReader::getFile()
{
    return fileToRead;
}

Image* MetadataReader::getArtwork()
{
    return nullptr;
}
