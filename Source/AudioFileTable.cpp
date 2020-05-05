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
AudioFileTable::AudioFileTable() : editMetadataButton("Edit Metadata")
{
    addAndMakeVisible(table);
    
    table.setModel(this);
    table.setHeader(new TableHeaderComponent);
    
    table.getHeader().addColumn("Track", 1, 50, 50, 50, 1);
    table.getHeader().addColumn("Track Name", 2, 150, 150, 150, 1);
    table.getHeader().addColumn("Artist Name", 3, 150, 150, 150, 1);
    table.getHeader().addColumn("Album Name", 4, 150, 150, 150, 1);
    table.getHeader().addColumn("Year", 5, 50, 50, 50, 1);
    table.getHeader().addColumn("File Type", 6, 50, 50, 50, 1);
    table.getHeader().addColumn("Selected", 7, 50, 50, 50, 1);
    
    table.setName("Table");
    
    addAndMakeVisible(editMetadataButton);
    editMetadataButton.setName("Edit Metadata Button");
    editMetadataButton.addListener(this);
    
}

AudioFileTable::~AudioFileTable()
{
    
}

void AudioFileTable::paint (Graphics& g)
{
    
}

void AudioFileTable::resized()
{
    table.setBounds(0, 0, getWidth(), getTableHeight());
    editMetadataButton.setBounds(0, getTableHeight(), 200, 30);
}

void AudioFileTable::setFiles(Array<File> filesToShow)
{
    metadataArray.ensureStorageAllocated(filesToShow.size());
    
    for(int i = 0; i < filesToShow.size(); i++)
    {
        TagLib_File* currentFile = taglib_file_new(filesToShow[i].getFullPathName().toRawUTF8());
        metadataArray.add(taglib_file_tag(currentFile));
        selectionButtons.add(new ToggleButton);
    }
    
    selectionButtons.add(new ToggleButton);
    selectionButtons[metadataArray.size()]->addListener(this);
    
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
    return (metadataArray.size() + 1)*table.getRowHeight()+table.getHeaderHeight();
}

int AudioFileTable::getNumRows()
{
    return metadataArray.size() + 1;
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
    g.drawLine(0, 0, width, 0);
}

void AudioFileTable::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(Colours::black);
    
    if(rowNumber != metadataArray.size())
    {
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
    
        //Artist Name column
        else if(columnId == 3)
        {
            g.drawText(String(taglib_tag_artist(metadataArray[rowNumber])), 2, 0, width, height, Justification::left);
        }
    
        //Album name column
        else if(columnId == 4)
        {
            g.drawText(String(taglib_tag_album(metadataArray[rowNumber])), 2, 0, width, height, Justification::left);
        }
    
        //Year column
        else if(columnId == 5)
        {
            g.drawText(String(taglib_tag_year(metadataArray[rowNumber])), 0, 0, width, height, Justification::centred);
        }
    
        //File Extention column
        else if(columnId == 6)
        {
            g.drawText(fileExtension, 2, 0, width, height, Justification::left);
        }
    }
    
    g.drawLine(width, 0, width, height);
}

Component* AudioFileTable::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if(columnId == 7)
    {
        return selectionButtons[rowNumber];
    }
    return nullptr;
}

void AudioFileTable::buttonClicked(Button* button)
{
    if(button == &editMetadataButton)
    {
        metadataWindow = new EditMetadataWindow();
        metadataWindow->setVisible(true);
    }
    else if(button == selectionButtons[metadataArray.size()])
    {
        for(int i = 0; i < metadataArray.size(); i++)
        {
            selectionButtons[i]->setToggleState(selectionButtons[metadataArray.size()]->getToggleState(), dontSendNotification);
        }
    }
}
