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
    
    for(int i = 0; i < filesToShow.size() + 1; i++)
    {
        if(i < filesToShow.size())
        {
            TagLib_File* currentFile = taglib_file_new(filesToShow[i].getFullPathName().toRawUTF8());
            metadataArray.add(taglib_file_tag(currentFile));
        }
        
        trackNumLabels.add(new Label);
        trackNumLabels[i]->setEditable(true);
        trackNumLabels[i]->setColour(Label::textColourId, Colours::black);
        trackNumLabels[i]->setJustificationType(Justification::centred);
        trackNumLabels[i]->addListener(this);
        
        trackNameLabels.add(new Label);
        trackNameLabels[i]->setEditable(true);
        trackNameLabels[i]->setColour(Label::textColourId, Colours::black);
        trackNameLabels[i]->addListener(this);
        
        artistNameLabels.add(new Label);
        artistNameLabels[i]->setEditable(true);
        artistNameLabels[i]->setColour(Label::textColourId, Colours::black);
        artistNameLabels[i]->addListener(this);
        
        albumNameLabels.add(new Label);
        albumNameLabels[i]->setEditable(true);
        albumNameLabels[i]->setColour(Label::textColourId, Colours::black);
        albumNameLabels[i]->addListener(this);
        
        yearLabels.add(new Label);
        yearLabels[i]->setEditable(true);
        yearLabels[i]->setColour(Label::textColourId, Colours::black);
        yearLabels[i]->addListener(this);
        
        selectionButtons.add(new ToggleButton);
        selectionButtons[i]->addListener(this);
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
    return (metadataArray.size() + 1)*table.getRowHeight()+table.getHeaderHeight();
}

int AudioFileTable::getNumRows()
{
    if(metadataArray.size() > 0)
    {
        return metadataArray.size() + 1;
    }
    else
    {
        return 0;
    }
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
        //File Extention column
        if(columnId == 6)
        {
            g.drawText(fileExtension, 2, 0, width, height, Justification::left);
        }
    }
    
    g.drawLine(width, 0, width, height);
}

Component* AudioFileTable::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if(columnId == 1)
    {
        if(rowNumber == metadataArray.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataArray.size() && comparatorFound != true; i++)
            {
                if(selectionButtons[i]->getToggleState() == true)
                {
                    comparatorFound = true;
                    comparatorString = trackNumLabels[i]->getText();
                }
            }
            
            if(comparatorFound == true)
            {
                bool differenceFound = false;
                
                for(int i = 0; i < metadataArray.size() && differenceFound != true; i++)
                {
                    if(selectionButtons[i]->getToggleState() == true)
                    {
                        if(trackNumLabels[i]->getText().compare(comparatorString) != 0)
                        {
                            differenceFound = true;
                        }
                    }
                }
                if(differenceFound == true)
                {
                    trackNumLabels[rowNumber]->setText("...", dontSendNotification);
                }
                else
                {
                    trackNumLabels[rowNumber]->setText(comparatorString, dontSendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                trackNumLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
            trackNumLabels[rowNumber]->setText(String(taglib_tag_track(metadataArray[rowNumber])), dontSendNotification);
        }
        return trackNumLabels[rowNumber];
    }
    
    else if(columnId == 2)
    {
        if(rowNumber == metadataArray.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataArray.size() && comparatorFound != true; i++)
            {
                if(selectionButtons[i]->getToggleState() == true)
                {
                    comparatorFound = true;
                    comparatorString = trackNameLabels[i]->getText();
                }
            }
            
            if(comparatorFound == true)
            {
                bool differenceFound = false;
                
                for(int i = 0; i < metadataArray.size() && differenceFound != true; i++)
                {
                    if(selectionButtons[i]->getToggleState() == true)
                    {
                        if(trackNameLabels[i]->getText().compare(comparatorString) != 0)
                        {
                            differenceFound = true;
                        }
                    }
                }
                if(differenceFound == true)
                {
                    trackNameLabels[rowNumber]->setText("...", dontSendNotification);
                }
                else
                {
                    trackNameLabels[rowNumber]->setText(comparatorString, dontSendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                trackNameLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
            trackNameLabels[rowNumber]->setText(String(taglib_tag_title(metadataArray[rowNumber])), dontSendNotification);
        }
        return trackNameLabels[rowNumber];
    }
    
    else if(columnId == 3)
    {
        if(rowNumber == metadataArray.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataArray.size() && comparatorFound != true; i++)
            {
                if(selectionButtons[i]->getToggleState() == true)
                {
                    comparatorFound = true;
                    comparatorString = artistNameLabels[i]->getText();
                }
            }
            
            if(comparatorFound == true)
            {
                bool differenceFound = false;
                
                for(int i = 0; i < metadataArray.size() && differenceFound != true; i++)
                {
                    if(selectionButtons[i]->getToggleState() == true)
                    {
                        if(artistNameLabels[i]->getText().compare(comparatorString) != 0)
                        {
                            differenceFound = true;
                        }
                    }
                }
                if(differenceFound == true)
                {
                    artistNameLabels[rowNumber]->setText("...", dontSendNotification);
                }
                else
                {
                    artistNameLabels[rowNumber]->setText(comparatorString, dontSendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                artistNameLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
            artistNameLabels[rowNumber]->setText(String(taglib_tag_artist(metadataArray[rowNumber])), dontSendNotification);
        }
        return artistNameLabels[rowNumber];
    }
    
    else if(columnId == 4)
    {
        if(rowNumber == metadataArray.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataArray.size() && comparatorFound != true; i++)
            {
                if(selectionButtons[i]->getToggleState() == true)
                {
                    comparatorFound = true;
                    comparatorString = albumNameLabels[i]->getText();
                }
            }
            
            if(comparatorFound == true)
            {
                bool differenceFound = false;
                
                for(int i = 0; i < metadataArray.size() && differenceFound != true; i++)
                {
                    if(selectionButtons[i]->getToggleState() == true)
                    {
                        if(albumNameLabels[i]->getText().compare(comparatorString) != 0)
                        {
                            differenceFound = true;
                        }
                    }
                }
                if(differenceFound == true)
                {
                    albumNameLabels[rowNumber]->setText("...", dontSendNotification);
                }
                else
                {
                    albumNameLabels[rowNumber]->setText(comparatorString, dontSendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                albumNameLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
             albumNameLabels[rowNumber]->setText(String(taglib_tag_album(metadataArray[rowNumber])), dontSendNotification);
        }
        return albumNameLabels[rowNumber];
    }
    
    else if(columnId == 5)
    {
        if(rowNumber == metadataArray.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataArray.size() && comparatorFound != true; i++)
            {
                if(selectionButtons[i]->getToggleState() == true)
                {
                    comparatorFound = true;
                    comparatorString = yearLabels[i]->getText();
                }
            }
            
            if(comparatorFound == true)
            {
                bool differenceFound = false;
                
                for(int i = 0; i < metadataArray.size() && differenceFound != true; i++)
                {
                    if(selectionButtons[i]->getToggleState() == true)
                    {
                        if(yearLabels[i]->getText().compare(comparatorString) != 0)
                        {
                            differenceFound = true;
                        }
                    }
                }
                if(differenceFound == true)
                {
                    yearLabels[rowNumber]->setText("...", dontSendNotification);
                }
                else
                {
                    yearLabels[rowNumber]->setText(comparatorString, dontSendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                yearLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
            yearLabels[rowNumber]->setText(String(taglib_tag_year(metadataArray[rowNumber])), dontSendNotification);
        }
        return yearLabels[rowNumber];
    }
    
    else if(columnId == 7)
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
            table.updateContent();
        }
    }
    else
    {
        for(int i = 0; i < metadataArray.size(); i++)
        {
            if(button == selectionButtons[i])
            {
                table.updateContent();
            }
        }
    }
}

void AudioFileTable::labelTextChanged(Label* label)
{
    for(int i = 0; i < metadataArray.size(); i++)
    {
        if(label == trackNumLabels[i])
        {
            taglib_tag_set_track(metadataArray[i], label->getText().getIntValue());
        }
        
        else if(label == trackNameLabels[i])
        {
            taglib_tag_set_title(metadataArray[i], label->getText().toUTF8());
        }
        
        else if(label == artistNameLabels[i])
        {
            taglib_tag_set_artist(metadataArray[i], label->getText().toUTF8());
        }
        
        else if(label == albumNameLabels[i])
        {
            taglib_tag_set_album(metadataArray[i], label->getText().toUTF8());
        }
        
        else if(label == yearLabels[i])
        {
            taglib_tag_set_year(metadataArray[i], label->getText().getIntValue());
        }
    }
}
