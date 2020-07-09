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

void DataHandler::setDataForItem(DataConcerned typeOfData, int itemIndex, const String& newData)
{
    if(itemIndex < readers.size())
    {
        switch (typeOfData)
        {
            case DataConcerned::trackNum:
                readers[itemIndex].object->setTrackNum(newData.getIntValue());
                break;
                
            case DataConcerned::trackTitle:
                readers[itemIndex].object->setTrackTitle(newData);
                break;
                
            case DataConcerned::artistName:
                readers[itemIndex].object->setArtistName(newData);
                break;
                
            case DataConcerned::albumName:
                readers[itemIndex].object->setAlbumName(newData);
                break;
                
            case DataConcerned::year:
                readers[itemIndex].object->setYear(newData.getIntValue());
                break;
                
            case DataConcerned::fileExtension:
                //ERROR
                break;
                
            case DataConcerned::fileName:
                readers[itemIndex].object->changeFileName(newData);
                break;
        }
    }
}

void DataHandler::setDataForSelectedItems(DataConcerned typeOfData, bool selected, const String& newData)
{
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i].selection)
        {
            setDataForItem(typeOfData, i, newData);
        }
    }
}

void DataHandler::moveItemToNewDirectory(int itemIndex, const String& newDirectory)
{
    readers[itemIndex].object->moveFileToNewDirectory(newDirectory);
}

void DataHandler::moveSelectedItemsToNewDirectory(const String& newDirectory, bool selected)
{
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i].selection == selected)
        {
            readers[i].object->moveFileToNewDirectory(newDirectory);
        }
    }
}

void DataHandler::moveItemBasedOnWildcard(int itemIndex, const String& newWildcardDirectory)
{
    manager.moveFileBasedOnWildcardPath(readers[itemIndex].object.get(), newWildcardDirectory);
}

void DataHandler::moveSelectedItemsBasedOnWildcards(const String& newWildcardDirectory, bool selected)
{
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i].selection == selected)
        {
            manager.moveFileBasedOnWildcardPath(readers[i].object.get(), newWildcardDirectory);
        }
    }
}

String DataHandler::getDataForItem(DataConcerned typeOfData, int index) const
{
    switch (typeOfData)
    {
        case DataConcerned::trackNum:
            return String(readers[index].object->getTrackNum());
            break;
                
        case DataConcerned::trackTitle:
            return readers[index].object->getTrackTitle();
            break;
                
        case DataConcerned::artistName:
            return readers[index].object->getArtistName();
            break;
                
        case DataConcerned::albumName:
            return readers[index].object->getAlbumName();
            break;
                
        case DataConcerned::year:
            return String(readers[index].object->getYear());
            break;
                
        case DataConcerned::fileExtension:
            return readers[index].object->getFile().getFileExtension();
            break;
            
        case DataConcerned::fileName:
            return readers[index].object->getFile().getFileNameWithoutExtension();
            break;
    }
}

void DataHandler::setItemSelection(int index, bool selected)
{
    readers[index].selection = selected;
}

void DataHandler::setItemSelection(int startIndex, int endIndex, bool selected)
{
    for(int i = startIndex; i < endIndex + 1; i++)
    {
        readers[i].selection = selected;
    }
}

void DataHandler::setAllItemsSelection(bool selected)
{
    for(int i = 0; i < readers.size(); i++)
    {
        readers[i].selection = selected;
    }
}

bool DataHandler::getItemSelection(int index) const
{
    return readers[index].selection;
}

bool DataHandler::isSelectedDataTheSame(DataConcerned typeOfData, bool selected)
{
    String comparisonString;
    
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i].selection == selected)
        {
            if(comparisonString.isEmpty())
            {
                comparisonString = getDataForItem(typeOfData, i);
            }
            
            else
            {
                if(getDataForItem(typeOfData, i).compare(comparisonString) != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

String DataHandler::getSimilarDataForSelectedItems(DataConcerned typeOfData)
{
    String comparisonString;
    
    for(int i = 0; i < readers.size(); i++)
    {
        if(readers[i].selection)
        {
            if(comparisonString.isEmpty())
            {
                comparisonString = getDataForItem(typeOfData, i);
            }
            
            else
            {
                if(getDataForItem(typeOfData, i).compare(comparisonString) != 0)
                {
                    return String();
                }
            }
        }
    }
    return comparisonString;
}

void DataHandler::addData(std::vector<std::unique_ptr<AudioMetadataReader>>& readersToAdd)
{
    for(int i = 0; i < readersToAdd.size(); i++)
    {
        readers.push_back(SelectionData<std::unique_ptr<AudioMetadataReader>>(std::move(readersToAdd[i]), false));
    }
}

void DataHandler::removeData(int index)
{
    //Bounds checking
    if(index >= 0 && index < numEntries())
    {
        readers.erase(readers.begin()+index);
    }
}


void DataHandler::removeData(int startIndex, int endIndex)
{
    if(startIndex >= 0 && endIndex >=0 && startIndex < numEntries() && endIndex < numEntries() && startIndex < endIndex)
    {
        readers.erase(readers.begin()+startIndex, readers.begin()+endIndex);
    }
}

int DataHandler::removeData(DataConcerned typeToCompare, const String& dataToCompare)
{
    int numRemoves = 0;
    
    for(int i = 0; i < numEntries(); i++)
    {
        if(getDataForItem(typeToCompare, i).compare(dataToCompare) == 0)
        {
            readers.erase(readers.begin()+i);
            numRemoves++;
        }
    }
    
    return numRemoves;
}

File& DataHandler::getFileForIndex(int index)
{
    return readers[index].object->getFile();
}

void DataHandler::printTest()
{
    for(int i = 0; i < numEntries(); i++)
    {
        DBG(readers[i].object->getTrackTitle());
    }
}

int DataHandler::numEntries()
{
    return readers.size();
}

bool compare(SelectionData<std::unique_ptr<AudioMetadataReader>>& first, SelectionData<std::unique_ptr<AudioMetadataReader>>& second)
{
    int artistCompareResult = first.object->getArtistName().compare(second.object->getArtistName());
    
    if(artistCompareResult != 0)
    {
        if(artistCompareResult < 0)
        {
            return true;
        }
        else if(artistCompareResult > 0)
        {
            return false;
        }
    }
    //Only get to here if artist names are the same
    
    int albumCompareResult = first.object->getAlbumName().compare(second.object->getAlbumName());
        
    if (albumCompareResult != 0)
    {
        if(artistCompareResult < 0)
        {
            return true;
        }
        else if(artistCompareResult > 0)
        {
            return false;
        }
    }
    
    if(first.object->getTrackNum() < second.object->getTrackNum())
    {
        return true;
    }
    
    return false;
}

void DataHandler::sort()
{
    std::sort(readers.begin(), readers.end(), compare);
}
