/*
  ==============================================================================

    ID3v2MetadataReader.cpp
    Created: 3 Jul 2020 11:06:40am
    Author:  Max Walley

  ==============================================================================
*/

#include "ID3v2MetadataReader.h"

ID3v2MetadataReader::ID3v2MetadataReader(const File& inputFile, TagLib::File* file, TagLib::ID3v2::Tag* tag) :   TagLibTagReader(inputFile, file), metadataTag(tag)
{
    std::cout << metadataTag->album() << std::endl;
}

ID3v2MetadataReader::~ID3v2MetadataReader()
{
    
}
