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
    
    //creates a new empty file
    std::optional<File> newFile = FileAndFolderCreator::createNewFolder(newPath);
    
    if(newFile != std::nullopt)
    {
        //Overwrites the old file with the new one
        fileToRead.moveFileTo(*newFile);
        fileToRead = *newFile;
    }
}

File& MetadataReader::getFile()
{
    return fileToRead;
}

Image* MetadataReader::getArtwork()
{
    return nullptr;
}
