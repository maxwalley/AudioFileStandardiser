/*
  ==============================================================================

    TagLibTagReader.cpp
    Created: 27 May 2020 6:37:30pm
    Author:  Max Walley

  ==============================================================================
*/

#include "TagLibTagReader.h"

TagLibTagReader::TagLibTagReader(const File& input)   :   AudioMetadataReader(input), metadataFile(fileToRead.getFullPathName().toUTF8(), false)
{
    metadata = metadataFile.tag();
    metadata->setGenre("");
    metadata->setComment("");
}

TagLibTagReader::~TagLibTagReader()
{
    metadataFile.save();
}

int TagLibTagReader::getTrackNum()
{
    return metadata->track();
}

String TagLibTagReader::getTrackTitle()
{
    return String(metadata->title().to8Bit());
    
    //return String(CharPointer_UTF8(metadata->title()));
}

String TagLibTagReader::getArtistName()
{
    return String(metadata->artist().to8Bit());
}

String TagLibTagReader::getAlbumName()
{
    return String(metadata->album().to8Bit());
}

int TagLibTagReader::getYear()
{
    return metadata->year();
}

void TagLibTagReader::setTrackNum(int newTrackNum)
{
    metadata->setTrack(newTrackNum);
}

void TagLibTagReader::setTrackTitle(const String& newTrackTitle)
{
    metadata->setTitle(TagLib::String(newTrackTitle.toUTF8()));
}

void TagLibTagReader::setArtistName(const String& newArtistName)
{
    metadata->setArtist(TagLib::String(newArtistName.toUTF8()));
}

void TagLibTagReader::setAlbumName(const String& newAlbumName)
{
    metadata->setAlbum(TagLib::String(newAlbumName.toUTF8()));
}

void TagLibTagReader::setYear(int newYear)
{
    metadata->setYear(newYear);
}
