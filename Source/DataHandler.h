/*
  ==============================================================================

    DataHandler.h
    Created: 10 Jun 2020 5:44:25pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "TagLibTagReader.h"

template <class t>
struct SelectionData
{
    //SelectionData(t newObject, bool newSelection)   :   object(newObject), selection(newSelection){};
    
    SelectionData(t&& newObject, bool newSelection) :   object(std::move(newObject)), selection(newSelection){};
    
    t object;
    bool selection;
};

class DataHandler
{
public:
    DataHandler();
    ~DataHandler();
    
    enum class DataConcerned
    {
        trackNum = 1,
        trackTitle = 2,
        artistName = 3,
        albumName = 4,
        year = 5,
        fileExtension = 6,
        fileName = 7
    };
    
    void setDataForItem(DataConcerned typeOfData, int itemIndex, const String& newData);
    
    void setDataForSelectedItems(DataConcerned typeOfData, bool selected, const String& newData);
    
    //Essentially a shortcut to stop the switch being explicitly implemented into lots of other funcs
    String getDataForItem(DataConcerned typeOfData, int index) const;
    
    void setItemSelection(int index, bool selected);
    void setItemSelection(int startIndex, int endIndex, bool selected);
    
    void setAllItemsSelection(bool selected);
    
    bool getItemSelection(int index) const;
    
    bool isSelectedDataTheSame(DataConcerned typeOfData, bool selected);
    
    //If no similar data is found will return an empty string
    String getSimilarDataForSelectedItems(DataConcerned typeOfData);
    
    void addData(std::vector<std::unique_ptr<AudioMetadataReader>>& readersToAdd);
    
    //Deletes item at index with bounds checking
    void removeData(int index);
    
    //Includes bounds checking
    void removeData(int startIndex, int endIndex);
    
    //removes data based on a comparison of the type set - returns the number of items removed
    int removeData(DataConcerned typeToCompare, const String& dataToCompare);
    
    void printTest();
    
    int numEntries();
    
    void sort();
    
private:
    
    std::vector<SelectionData<std::unique_ptr<AudioMetadataReader>>> readers;
};
