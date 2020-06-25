/*
  ==============================================================================

    DataHandler.h
    Created: 10 Jun 2020 5:44:25pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "TagLibTagReader.h"
#include "Mediator.h"

template <class t>
struct SelectionData
{
    SelectionData(t newObject, bool newSelection)   :   object(newObject), selection(newSelection){};
    
    //SelectionData(const SelectionData& otherData){};
    
    t object;
    bool selection;
};

class DataHandler
{
public:
    DataHandler();
    ~DataHandler();
    
    enum DataConcerned
    {
        trackNum = 0,
        trackTitle = 1,
        artistName = 2,
        albumName = 3,
        year = 4,
        fileName = 5,
        fileExtension = 6
    };
    
    void setDataForItem(DataConcerned typeOfData, int itemIndex, String newData);
    
    //Essentially a shortcut to stop the switch being explicitly implemented into lots of other funcs
    String getDataForItem(DataConcerned typeOfData, int index);
    
    void setItemSelection(int index, bool selected);
    bool getItemSelection(int index) const;
    
    bool isSelectedDataTheSame(DataConcerned typeOfData, bool selected);
    
    void addData(std::vector<AudioMetadataReader*>& readersToAdd);
    void addData(AudioMetadataReader* readerToAdd);
    
    void clearData();
    void clearData(int firstIndex, int lastIndex);
    
    int numEntries();
    
    void sort();
    
private:
    
    std::vector<SelectionData<AudioMetadataReader*>> readers;
};
