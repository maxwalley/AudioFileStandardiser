/*
  ==============================================================================

    ID3v2MetadataReader.cpp
    Created: 3 Jul 2020 11:06:40am
    Author:  Max Walley

  ==============================================================================
*/

#include "ID3v2MetadataReader.h"
#include "attachedpictureframe.h"

ID3v2MetadataReader::ID3v2MetadataReader(std::unique_ptr<TagLib::File> file, TagLib::ID3v2::Tag* associatedTag) :   TagLibTagReader(std::move(file)), metadataTag(associatedTag), coverArt(extractImage(metadataTag))
{
    
}

ID3v2MetadataReader::~ID3v2MetadataReader()
{
    
}

MetadataReader::MetadataType ID3v2MetadataReader::getMetadataType() const
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
