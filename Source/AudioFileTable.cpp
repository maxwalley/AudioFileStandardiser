/*
  ==============================================================================

    AudioFileTable.cpp
    Created: 2 May 2020 5:25:10pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioFileTable.h"

int TagLib_TagSorter::compareElements(TagLib_Tag* first, TagLib_Tag* second)
{
    if(taglib_tag_track(first) > taglib_tag_track(second))
    {
        return 1;
    }
    else if(taglib_tag_track(first) == taglib_tag_track(second))
    {
        return 0;
    }
    else if(taglib_tag_track(first) < taglib_tag_track(second))
    {
        return -1;
    }
}



//==============================================================================
AudioFileTable::AudioFileTable()
{
    addAndMakeVisible(table);
    
    table.setModel(this);
    table.setHeader(new TableHeaderComponent);
    
    table.getHeader().addColumn("Track Num", 1, 50, 50, 50, 1);
    table.getHeader().addColumn("Track Name", 2, 200, 200, 200, 1);
    table.getHeader().addColumn("Artist Name", 3, 100, 100, 100, 1);
    
    table.setName("Table");
    header.setName("Header");
    
}

AudioFileTable::~AudioFileTable()
{
    
}

void AudioFileTable::paint (Graphics& g)
{
    
}

void AudioFileTable::resized()
{
    table.setBounds(0, 0, getWidth(), getHeight());
}

void AudioFileTable::setFiles(Array<File> filesToShow)
{
    metadataArray.ensureStorageAllocated(filesToShow.size());
    
    for(int i = 0; i < filesToShow.size(); i++)
    {
        TagLib_File* currentFile = taglib_file_new(filesToShow[i].getFullPathName().toRawUTF8());
        metadataArray.add(taglib_file_tag(currentFile));
    }
    
    metadataArray.sort(arraySorter);
    
    fileExtension = filesToShow[0].getFileExtension();
    
    table.updateContent();
}

void AudioFileTable::refreshTable()
{
    table.updateContent();
}

int AudioFileTable::getTableHeight()
{
    return metadataArray.size()*table.getRowHeight()+table.getHeaderHeight();
}

int AudioFileTable::getNumRows()
{
    return metadataArray.size();
}

void AudioFileTable::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if(rowNumber % 2 == 0)
    {
        g.fillAll(Colours::silver);
    }
    else
    {
        g.fillAll(Colours::lightgrey);
    }
}

void AudioFileTable::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(Colours::black);
    
    //Track Num column
    if(columnId == 1)
    {
        g.drawText(String(taglib_tag_track(metadataArray[rowNumber])), 2, 0, width, height, Justification::centred);
    }
    
    //Track Name column
    else if(columnId == 2)
    {
        g.drawText(String(taglib_tag_title(metadataArray[rowNumber])), 2, 0, width, height, Justification::left);
    }
    
    //File Extention column
    else if(columnId == 3)
    {
        g.drawText(fileExtension, 2, 0, width, height, Justification::left);
    }
    
    g.drawLine(0, 0, 0, height);
    g.drawLine(0, 0, width, 0);
}
