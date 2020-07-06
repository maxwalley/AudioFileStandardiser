/*
  ==============================================================================

    ID3v2MetadataReader.cpp
    Created: 3 Jul 2020 11:06:40am
    Author:  Max Walley

  ==============================================================================
*/

#include "ID3v2MetadataReader.h"

ID3v2MetadataReader::ID3v2MetadataReader(std::unique_ptr<TagLib::File> file) :   TagLibTagReader(std::move(file)), metadataTag(findTag(metadataFile.get()))
{
    std::cout << metadataTag->album() << std::endl;
}

ID3v2MetadataReader::~ID3v2MetadataReader()
{
    
}

TagLib::ID3v2::Tag* ID3v2MetadataReader::findTag(TagLib::File* inputFile)
{
    unsigned long fileNameLength = std::strlen(inputFile->name());
    unsigned long fileExtensionStartIndex = 0;
    
    //Extracts the file extension
    for(unsigned long i = fileNameLength - 1; i >= 0; i--)
    {
        //Finds the last occurance full stop
        if(inputFile->name()[i] == '.')
        {
            fileExtensionStartIndex = i;
            break;
        }
    }
    
    //If the file extension is .mp3
    if(std::strcmp(inputFile->name() + fileExtensionStartIndex, ".mp3") == 0)
    {
        TagLib::MPEG::File* convertedFile = dynamic_cast<TagLib::MPEG::File*>(inputFile);
        
        return convertedFile->ID3v2Tag();
    }
    
    return nullptr;
}
