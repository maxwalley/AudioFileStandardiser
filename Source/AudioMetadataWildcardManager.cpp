/*
  ==============================================================================

    FilePathWildcardInterpretter.cpp
    Created: 5 Jun 2020 4:54:11pm
    Author:  Max Walley

  ==============================================================================
*/

#include "AudioMetadataWildcardManager.h"

String AudioMetadataWildcardManager::convertWildcardToString (AudioMetadataReader* reader, const String& string) const
{
    if(string == "$artist")
    {
        return reader->getArtistName();
    }
    
    else if (string == "$album")
    {
        return reader->getAlbumName();
    }
    
    else if (string == "$title")
    {
        return reader->getTrackTitle();
    }
    
    else if (string == "$year")
    {
        return String(reader->getYear());
    }
    
    else if (string == "$fileformat")
    {
        return reader->getFile().getFileExtension();
    }
    
    else if (string == "$tracknum")
    {
        String trackNumString = String(reader->getTrackNum());
        
        if(currentTrackNumFormat != minimumSingleDigit)
        {
            if(reader->getTrackNum() < 10 && reader->getTrackNum() >= 0)
            {
                trackNumString = "0" + trackNumString;
            }
            
            if(currentTrackNumFormat == minimumTripleDigit)
            {
                if(reader->getTrackNum() < 100 && reader->getTrackNum() >= 0)
                {
                    trackNumString = "0" + trackNumString;
                }
            }
        }
        
        return trackNumString;
    }
    return string;
}

StringArray AudioMetadataWildcardManager::getCompatibleWildcards() const
{
    return compatibleWildcards;
}

void AudioMetadataWildcardManager::setTrackNumFormat(trackNumFormat newFormat)
{
    currentTrackNumFormat = newFormat;
}
