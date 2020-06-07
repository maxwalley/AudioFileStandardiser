/*
  ==============================================================================

    FormatMetadataReader.cpp
    Created: 7 Jun 2020 3:02:17pm
    Author:  Max Walley

  ==============================================================================
*/

#include "FormatMetadataReader.h"

FormatMetadataReader::FormatMetadataReader(File& inputFile) :   fileToRead(inputFile)
{
    
}

FormatMetadataReader::~FormatMetadataReader()
{
    
}

void FormatMetadataReader::moveFileToNewDirectory(String newLocation)
{
    newLocation = newLocation + "/" + fileToRead.getFileName();
    fileToRead.moveFileTo(File(newLocation));
    fileToRead = newLocation;
}

String FormatMetadataReader::getFileLocation()
{
    return fileToRead.getFullPathName();
}

String FormatMetadataReader::getFileName()
{
    return fileToRead.getFileName();
}

String FormatMetadataReader::getFileNameWithoutExtension()
{
    return fileToRead.getFileNameWithoutExtension();
}

String FormatMetadataReader::getFileExtension()
{
    return fileToRead.getFileExtension();
}

void FormatMetadataReader::changeFileName(String newName)
{
    String newPath = fileToRead.getFullPathName().replace(fileToRead.getFileNameWithoutExtension(), newName);
    fileToRead.moveFileTo(File(newPath));
    fileToRead = newPath;
}
