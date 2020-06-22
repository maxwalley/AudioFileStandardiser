/*
  ==============================================================================

    DataHandler.cpp
    Created: 10 Jun 2020 5:44:25pm
    Author:  Max Walley

  ==============================================================================
*/

#include "DataHandler.h"

DataHandler::DataHandler()
{
    
}

DataHandler::~DataHandler()
{
    
}

void DataHandler::setDataForItem(DataConcerned typeOfData, int itemIndex, String newData)
{
    if(itemIndex < readers.size())
    {
        switch (typeOfData)
        {
            case trackNum:
                readers[itemIndex]->setTrackNum(newData.getIntValue());
                break;
                
            case trackTitle:
                readers[itemIndex]->setTrackTitle(newData);
                break;
                
            case artistName:
                readers[itemIndex]->setArtistName(newData);
                break;
                
            case albumName:
                readers[itemIndex]->setAlbumName(newData);
                break;
                
            case year:
                readers[itemIndex]->setYear(newData.getIntValue());
                break;
                
            case fileName:
                readers[itemIndex]->changeFileName(newData);
                break;
                
            case fileExtension:
                //ERROR
                break;
        }
    }
}

String DataHandler::getDataForItem(DataConcerned typeOfData, AudioMetadataReader* reader)
{
    if(reader != nullptr)
    {
        switch (typeOfData)
        {
            case trackNum:
                return String(reader->getTrackNum());
                break;
                
            case trackTitle:
                return reader->getTrackTitle();
                break;
                
            case artistName:
                return reader->getArtistName();
                break;
                
            case albumName:
                return reader->getAlbumName();
                break;
                
            case year:
                return String(reader->getYear());
                break;
                
            case fileName:
                return reader->getFile().getFileNameWithoutExtension();
                break;
                
            case fileExtension:
                return reader->getFile().getFileExtension();
                break;
        }
    }
}

bool DataHandler::isSelectedDataTheSame(DataConcerned typeOfData, bool selected)
{
    std::vector<AudioMetadataReader*> tempReaders = readers.getItemsBasedOnSelection(selected);
    
    if(tempReaders.size() != 0)
    {
        bool differenceFound = false;
        String comparatorString = getDataForItem(typeOfData, tempReaders[0]);
        
        for(int i = 1; i < tempReaders.size() && !differenceFound; i++)
        {
            if(getDataForItem(typeOfData, tempReaders[i]) != comparatorString)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

int DataHandler::getIndexForArtist(String artistName)
{
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i]->getArtistName().compare(artistName) == 0)
        {
            return i;
        }
    }
    return -1;
}

int DataHandler::getIndexForAlbum(String albumName)
{
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i]->getAlbumName().compare(albumName) == 0)
        {
            return i;
        }
    }
    return -1;
}

int DataHandler::getIndexForTrack(String trackTitle)
{
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i]->getTrackTitle().compare(trackTitle) == 0)
        {
            return i;
        }
    }
    return -1;
}

bool DataHandler::compareDataAtIndexes(DataConcerned typeOfData, int index1, int index2)
{
    if(getDataForItem(typeOfData, readers[index1]) != getDataForItem(typeOfData, readers[index2]))
    {
        return false;
    }
    return true;
}

bool DataHandler::compareDataAtIndexes(DataConcerned typeOfData, std::vector<int> indexesToCompare)
{
    if(indexesToCompare.size() == 0)
    {
        return false;
    }
    else
    {
        String comparisonString = getDataForItem(typeOfData, readers[indexesToCompare[0]]);
        
        for(int i = 1; i < indexesToCompare.size(); i++)
        {
            if(getDataForItem(typeOfData, readers[indexesToCompare[i]]).compare(comparisonString) != 0)
            {
                return false;
            }
        }
        return true;
    }
}
