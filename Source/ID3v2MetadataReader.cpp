/*
  ==============================================================================

    ID3v2MetadataReader.cpp
    Created: 3 Jul 2020 11:06:40am
    Author:  Max Walley

  ==============================================================================
*/

#include "ID3v2MetadataReader.h"
#include "attachedpictureframe.h"

ID3v2MetadataReader::ID3v2MetadataReader(std::unique_ptr<TagLib::File> file) :   TagLibTagReader(std::move(file)), metadataTag(findTag(metadataFile.get())), coverArt(extractImage(metadataTag))
{
    
}

ID3v2MetadataReader::~ID3v2MetadataReader()
{
    
}

MetadataReader::MetadataType ID3v2MetadataReader::getMetadataType()
{
    return MetadataType::ID3v2;
}

Image* ID3v2MetadataReader::getArtwork()
{
    if(coverArt.isValid())
    {
        return &coverArt;
    }
    return nullptr;
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
        
        if(!convertedFile->hasID3v2Tag())
        {
            return nullptr;
        }
        
        return convertedFile->ID3v2Tag();
    }
    
    return nullptr;
}

Image ID3v2MetadataReader::extractImage(TagLib::ID3v2::Tag* metadata)
{
    int numFrames = metadata->frameList("APIC").size();
    
    for(int i = 0; i < numFrames; i++)
    {
        TagLib::ID3v2::AttachedPictureFrame* frame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(metadata->frameList("APIC")[i]);
            
        if(frame->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover)
        {
            //Image testImage = ImageFileFormat::loadFrom(frame->picture().data(), frame->size());
        
            Image testImage = ImageCache::getFromMemory(frame->picture().data(), frame->size());
            
            return testImage;
        }
    }
    
    //returns a null image
    return Image();
}
