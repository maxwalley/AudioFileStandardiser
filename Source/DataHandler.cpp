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
    //clearData();
}

void DataHandler::setDataForItem(DataConcerned typeOfData, int itemIndex, String newData)
{
    if(itemIndex < readers.size())
    {
        switch (typeOfData)
        {
            case trackNum:
                readers[itemIndex].object->setTrackNum(newData.getIntValue());
                break;
                
            case trackTitle:
                readers[itemIndex].object->setTrackTitle(newData);
                break;
                
            case artistName:
                readers[itemIndex].object->setArtistName(newData);
                break;
                
            case albumName:
                readers[itemIndex].object->setAlbumName(newData);
                break;
                
            case year:
                readers[itemIndex].object->setYear(newData.getIntValue());
                break;
                
            case fileName:
                readers[itemIndex].object->changeFileName(newData);
                break;
                
            case fileExtension:
                //ERROR
                break;
        }
    }
}

String DataHandler::getDataForItem(DataConcerned typeOfData, int index)
{
    switch (typeOfData)
    {
        case trackNum:
            return String(readers[index].object->getTrackNum());
            break;
                
        case trackTitle:
            return readers[index].object->getTrackTitle();
            break;
                
        case artistName:
            return readers[index].object->getArtistName();
            break;
                
        case albumName:
            return readers[index].object->getAlbumName();
            break;
                
        case year:
            return String(readers[index].object->getYear());
            break;
                
        case fileName:
            return readers[index].object->getFile().getFileNameWithoutExtension();
            break;
                
        case fileExtension:
            return readers[index].object->getFile().getFileExtension();
            break;
    }
}

void DataHandler::setItemSelection(int index, bool selected)
{
    readers[index].selection = selected;
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

/*void DataHandler::addData(std::vector<AudioMetadataReader*>& readersToAdd)
{
    for(int i = 0; i < readersToAdd.size(); i++)
    {
        readers.push_back(SelectionData<AudioMetadataReader*>(readersToAdd[i], false));
    }
}*/

void DataHandler::addData(std::vector<std::unique_ptr<AudioMetadataReader>>& readersToAdd)
{
    for(int i = 0; i < readersToAdd.size(); i++)
    {
        readers.push_back(SelectionData<std::unique_ptr<AudioMetadataReader>>(std::move(readersToAdd[i]), false));
    }
}

void DataHandler::printTest()
{
    for(int i = 0; i < numEntries(); i++)
    {
        DBG(readers[i].object->getTrackTitle());
    }
}

/*void DataHandler::addData(AudioMetadataReader* readerToAdd)
{
    readers.push_back(SelectionData<AudioMetadataReader*>(readerToAdd, false));
}

/*void DataHandler::addData(const std::vector<std::unique_ptr<AudioMetadataReader>>& readersToAdd)
{
    for(int i = 0; i < readersToAdd.size(); i++)
    {
        //readers.push_back(SelectionData<AudioMetadataReader*>(readersToAdd[i], false));
        
        readers.push_back(SelectionData<std::unique_ptr<AudioMetadataReader>>())
    }
}

void DataHandler::addData(std::unique_ptr<AudioMetadataReader> readerToAdd)
{
    SelectionData<std::unique_ptr<AudioMetadataReader>> temp = {std::move(readerToAdd), false};
    
    readerToAdd = nullptr;
    
    readers.push_back(temp);
}

void DataHandler::clearData()
{
    for(int i = 0; i < readers.size(); i++)
    {
        delete readers[i].object;
    }
    
    readers.clear();
}

void DataHandler::clearData(int firstIndex, int lastIndex)
{
    if(firstIndex <= lastIndex && firstIndex < numEntries() && lastIndex < numEntries() && firstIndex > 0 && lastIndex > 0)
    {
        for(int i = firstIndex; i < lastIndex; i++)
        {
            delete readers[i].object;
        }
    
        readers.erase(readers.begin() + firstIndex, readers.begin() + lastIndex);
    }
}
*/
int DataHandler::numEntries()
{
    return readers.size();
}

bool compare(SelectionData<AudioMetadataReader*> first, SelectionData<AudioMetadataReader*> second)
{
    if(first.object->getArtistName().compare(second.object->getArtistName()) < 0)
    {
        return false;
    }
    return true;
}

/*void DataHandler::sort()
{
    std::sort(readers.begin(), readers.end(), compare);
}*/
