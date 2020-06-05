/*
  ==============================================================================

    FilePathWildcardInterpretter.cpp
    Created: 5 Jun 2020 4:54:11pm
    Author:  Max Walley

  ==============================================================================
*/

#include "FilePathWildcardInterpretter.h"

FilePathWildcardInterpretter::FilePathWildcardInterpretter()    :   currentTrackNumFormat(minimumSingleDigit)
{
    compatibleWildcards = {"$artist", "$album", "$tracknum", "$tracktitle", "$year", "$fileformat"};
}

FilePathWildcardInterpretter::~FilePathWildcardInterpretter()
{
    
}

void FilePathWildcardInterpretter::setTrackNumFormat()
{
    
}

StringArray FilePathWildcardInterpretter::getCompatibleWildcards() const
{
    return compatibleWildcards;
}

String FilePathWildcardInterpretter::interpretString(String input, FormatMetadataReader* file)
{
    String stringToReturn = input;
    
    //Checks that there is a wildcard in the input string
    if(stringToReturn.contains("$"))
    {
        stringToReturn = stringToReturn.replace("$artist", file->getArtistName());
        stringToReturn = stringToReturn.replace("$album", file->getAlbumName());
        
        String trackNumString = String(file->getTrackNum());
        
        if(currentTrackNumFormat != minimumSingleDigit)
        {
            if(file->getTrackNum() < 10 && file->getTrackNum() >= 0)
            {
                trackNumString = "0" + trackNumString;
            }
            
            if(currentTrackNumFormat == minimumTripleDigit)
            {
                if(file->getTrackNum() < 100 && file->getTrackNum() >= 0)
                {
                    trackNumString = "0" + trackNumString;
                }
            }
        }
        
        stringToReturn = stringToReturn.replace("$tracknum", trackNumString);
        
        stringToReturn = stringToReturn.replace("$tracktitle", file->getTrackTitle());
        stringToReturn = stringToReturn.replace("$year", String(file->getYear()));
        stringToReturn = stringToReturn.replace("$fileformat", file->getFileExtension());
    }
    
    return stringToReturn;
}
