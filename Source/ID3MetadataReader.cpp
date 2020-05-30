/*
  ==============================================================================

    ID3MetadataReader.cpp
    Created: 27 May 2020 6:37:30pm
    Author:  Max Walley

  ==============================================================================
*/

#include "ID3MetadataReader.h"

ID3MetadataReader::ID3MetadataReader(File& input)
{
    file = input;
    metadataFile = taglib_file_new(input.getFullPathName().toRawUTF8());
    metadata = taglib_file_tag(metadataFile);
}

ID3MetadataReader::~ID3MetadataReader()
{
    taglib_file_save(metadataFile);
    taglib_file_free(metadataFile);
}

int ID3MetadataReader::getTrackNum()
{
    return taglib_tag_track(metadata);
}

String ID3MetadataReader::getTrackTitle()
{
    return String(CharPointer_UTF8(taglib_tag_title(metadata)));
}

String ID3MetadataReader::getArtistName()
{
    return String(CharPointer_UTF8(taglib_tag_artist(metadata)));
}

String ID3MetadataReader::getAlbumName()
{
    return String(CharPointer_UTF8(taglib_tag_album(metadata)));
}

int ID3MetadataReader::getYear()
{
    return taglib_tag_year(metadata);
}

void ID3MetadataReader::setTrackNum(int newTrackNum)
{
    taglib_tag_set_track(metadata, newTrackNum);
}

void ID3MetadataReader::setTrackTitle(String newTrackTitle)
{
    taglib_tag_set_title(metadata, newTrackTitle.toUTF8());
}

void ID3MetadataReader::setArtistName(String newArtistName)
{
    taglib_tag_set_artist(metadata, newArtistName.toUTF8());
}

void ID3MetadataReader::setAlbumName(String newAlbumName)
{
    taglib_tag_set_album(metadata, newAlbumName.toUTF8());
}

void ID3MetadataReader::setYear(int newYear)
{
    taglib_tag_set_year(metadata, newYear);
}

void ID3MetadataReader::moveFile(String newLocation)
{
    file.moveFileTo(File(newLocation));
    file = newLocation;
}

String ID3MetadataReader::getFileLocation()
{
    return file.getFullPathName();
}

String ID3MetadataReader::getFileName()
{
    return file.getFileName();
}

String ID3MetadataReader::getFileNameWithoutExtension()
{
    return file.getFileNameWithoutExtension();
}
