/*
  ==============================================================================

    DataHandler.h
    Created: 10 Jun 2020 5:44:25pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "SelectionArray.h"
#include "TagLibTagReader.h"

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
    String getDataForItem(DataConcerned typeOfData, AudioMetadataReader* reader);
    
    bool isSelectedDataTheSame(DataConcerned typeOfData, bool selected);
    
    int getIndexForArtist(String artistName);
    
    int getIndexForAlbum(String albumName);
    
    int getIndexForTrack(String trackTitle);
    
    bool compareDataAtIndexes(DataConcerned typeOfData, int index1, int index2);
    
    bool compareDataAtIndexes(DataConcerned typeOfData, std::vector<int> indexesToCompare);
    
private:
    
    SelectionArray<AudioMetadataReader> readers;
    
};
