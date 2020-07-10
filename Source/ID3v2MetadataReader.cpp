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
    int numFrames = metadata->frameList().size();
    
    for(int i = 0; i < numFrames; i++)
    {
        std::cout << "Frame number " << i+1 << "is a " << metadataTag->frameList()[i]->toString().to8Bit() << std::endl;
        
        if(metadata->frameList()[i]->toString() == "[image/jpeg]")
        {
            TagLib::ID3v2::AttachedPictureFrame* frame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(metadata->frameList()[i]);
            
            
            Image testImage = ImageFileFormat::loadFrom(frame->picture().data(), frame->size());
            
            std::cout << testImage.isValid() << std::endl;
        }
    }
}
