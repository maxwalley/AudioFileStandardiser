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
AudioFileTable::AudioFileTable() : correctDataButton("Correct Data"), saveButton("Save Data"), changeLocationButton("Change File Locations"), fileNamesToChangeWithTitle(true), showBatchControls(false)
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
    
    addAndMakeVisible(correctDataButton);
    correctDataButton.setName("correctData");
    correctDataButton.addListener(this);
    
    addAndMakeVisible(saveButton);
    saveButton.setName("saveButton");
    saveButton.addListener(this);
    
    addAndMakeVisible(changeLocationButton);
    changeLocationButton.setName("changeLocationButton");
    changeLocationButton.addListener(this);
    
    addAndMakeVisible(batchControlViewport);
    batchControlViewport.setVisible(false);
    batchControlViewport.setViewedComponent(&batchControls);
    
    batchControls.addActionListener(this);
}

AudioFileTable::~AudioFileTable()
{
    saveTableToTags();
    
    for(int i = 0; i < metadataFiles.size(); i++)
    {
        taglib_file_save(metadataFiles[i]);
        taglib_file_free(metadataFiles[i]);
    }
}

void AudioFileTable::paint (Graphics& g)
{
    
}

void AudioFileTable::resized()
{
    if(showBatchControls == false)
    {
        table.setBounds(0, 0, getWidth(), getTableHeight());
        batchControls.setVisible(false);
        batchControlViewport.setVisible(false);
    }
    else
    {
        table.setBounds(0, 0, getWidth() - 200, getTableHeight());
        batchControlViewport.setBounds(650, 0, 200, getHeight());
        batchControlViewport.setVisible(true);
        batchControls.setSize(190, 600);
        batchControls.setVisible(true);
    }
    
    correctDataButton.setBounds(0, getTableHeight(), 200, 30);
    saveButton.setBounds(200, getTableHeight(), 200, 30);
    changeLocationButton.setBounds(400, getTableHeight(), 200, 30);
}

void AudioFileTable::setFiles(Array<File>& filesToShow)
{
    metadataArray.ensureStorageAllocated(filesToShow.size());
    
    filesToShow.swapWith(juceFiles);
    
    for(int i = 0; i < juceFiles.size() + 1; i++)
    {
        if(i == 0)
        {
            currentDirectoryPath = juceFiles[i].getFullPathName().dropLastCharacters(filesToShow[i].getFileName().length());
        }
        
        if(i < juceFiles.size())
        {
            TagLib_File* currentFile = taglib_file_new(juceFiles[i].getFullPathName().toRawUTF8());
            metadataFiles.add(currentFile);
            metadataArray.add(taglib_file_tag(currentFile));
            
            DBG("Here");
            metadataReaders.add(metadataManager.createMetadataReader(juceFiles.getReference(i)));
            
            DBG(metadataReaders[i]->getTrackNum());
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
        
        batchControls.setDataSet(true);
    }
    
    metadataArray.sort(arraySorter);
    
    fileExtension = juceFiles[0].getFileExtension();
    
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

void AudioFileTable::setFileNamesToChangeWithTitle(bool change)
{
    fileNamesToChangeWithTitle = change;
}

void AudioFileTable::setBatchControlsVisible(bool visible)
{
    showBatchControls = visible;
    resized();
}

void AudioFileTable::addBatchControlsActionListener(ActionListener* listener)
{
    batchControls.addActionListener(listener);
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
    
    if(columnId == 6)
    {
        g.drawText(fileExtension, 0, 0, width, height, Justification::centred);
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
                    //Dont send notification so it doesnt change all labels to "..."
                    trackNumLabels[rowNumber]->setText("...", dontSendNotification);
                }
                else
                {
                    trackNumLabels[rowNumber]->setText(comparatorString, sendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                //Dont send notification so it doesnt change all labels to "..."
                trackNumLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
            trackNumLabels[rowNumber]->setText(String(taglib_tag_track(metadataArray[rowNumber])), sendNotification);
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
                    trackNameLabels[rowNumber]->setText(comparatorString, sendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                trackNameLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
            trackNameLabels[rowNumber]->setText(String(CharPointer_UTF8(taglib_tag_title(metadataArray[rowNumber]))), sendNotification);
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
                    artistNameLabels[rowNumber]->setText(comparatorString, sendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                artistNameLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
            artistNameLabels[rowNumber]->setText(String(CharPointer_UTF8(taglib_tag_artist(metadataArray[rowNumber]))), sendNotification);
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
                    albumNameLabels[rowNumber]->setText(comparatorString, sendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                albumNameLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
             albumNameLabels[rowNumber]->setText(String(CharPointer_UTF8(taglib_tag_album(metadataArray[rowNumber]))), sendNotification);
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
                    yearLabels[rowNumber]->setText(comparatorString, sendNotification);
                }
            }
            else if(comparatorFound == false)
            {
                yearLabels[rowNumber]->setText("...", dontSendNotification);
            }
        }
        else
        {
            yearLabels[rowNumber]->setText(String(taglib_tag_year(metadataArray[rowNumber])), sendNotification);
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
    if(button == &correctDataButton)
    {
        StringChecker checker;
        
        for(int i = 0; i < metadataArray.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                trackNameLabels[i]->setText(checker.decapatalizeWords(trackNameLabels[i]->getText()), sendNotification);
                albumNameLabels[i]->setText(checker.decapatalizeWords(albumNameLabels[i]->getText()), sendNotification);
                artistNameLabels[i]->setText(checker.decapatalizeWords(artistNameLabels[i]->getText()), sendNotification);
            }
        }
    }
    
    else if(button == &saveButton)
    {
        saveTableToTags();
    }
    
    else if(button == &changeLocationButton)
    {
        FileChooser chooser("Select A New Location");
        String newDirectory;
        
        if(chooser.browseForDirectory())
        {
            currentDirectoryPath = chooser.getResult().getFullPathName() + "/";
            //DBG(currentDirectoryPath);
        
            for(int i = 0; i < metadataArray.size(); i++)
            {
                /*File temp(currentDirectoryPath + (*juceFiles)[i].getFileName());
                (*juceFiles)[i].moveFileTo(temp);
                juceFiles->set(i, temp);
            
                //Replaces the metadata array
                taglib_file_free(metadataFiles[i]);
                
                TagLib_File* currentFile = taglib_file_new((currentDirectoryPath + "/" + (*juceFiles)[i].getFileName()).toRawUTF8());*/
                
                //metadataFiles.set(i,currentFile);
                //metadataArray.set(i, taglib_file_tag(currentFile));
    
            }
        }
    }
    
    else if(button == selectionButtons[metadataArray.size()])
    {
        for(int i = 0; i < metadataArray.size(); i++)
        {
            selectionButtons[i]->setToggleState(selectionButtons[metadataArray.size()]->getToggleState(), sendNotification);
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
    //The change all label for the track number field
    if(label == trackNumLabels[metadataArray.size()])
    {
        for(int i = 0; i < metadataArray.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                trackNumLabels[i]->setText(trackNumLabels[metadataArray.size()]->getText(), sendNotification);
            }
        }
    }
    
    //The change all label for the track name field
    else if(label == trackNameLabels[metadataArray.size()])
    {
        for(int i = 0; i < metadataArray.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                trackNameLabels[i]->setText(trackNameLabels[metadataArray.size()]->getText(), sendNotification);
            }
        }
    }
    
    //The change all label for the artist name field
    else if(label == artistNameLabels[metadataArray.size()])
    {
        for(int i = 0; i < metadataArray.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                artistNameLabels[i]->setText(artistNameLabels[metadataArray.size()]->getText(), sendNotification);
            }
        }
    }
    
    //The change all label for the album name field
    else if(label == albumNameLabels[metadataArray.size()])
    {
        for(int i = 0; i < metadataArray.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                albumNameLabels[i]->setText(albumNameLabels[metadataArray.size()]->getText(), sendNotification);
            }
        }
    }
    
    //The change all label for the year field
    else if(label == yearLabels[metadataArray.size()])
    {
        for(int i = 0; i < metadataArray.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                yearLabels[i]->setText(yearLabels[metadataArray.size()]->getText(), sendNotification);
            }
        }
    }
    
    else
    {
        //Runs through the arrays and checks to find the label. Then saves the new tag with the label value
        for(int i = 0; i < metadataArray.size(); i++)
        {
            if(label == trackNumLabels[i])
            {
                taglib_tag_set_track(metadataArray[i], trackNumLabels[i]->getText().getIntValue());
            }
            else if(label == trackNameLabels[i])
            {
                taglib_tag_set_title(metadataArray[i], trackNameLabels[i]->getText().toUTF8());
            }
            else if(label == artistNameLabels[i])
            {
                taglib_tag_set_artist(metadataArray[i], artistNameLabels[i]->getText().toUTF8());
            }
            else if(label == albumNameLabels[i])
            {
                taglib_tag_set_album(metadataArray[i], albumNameLabels[i]->getText().toUTF8());
            }
            else if(label == yearLabels[i])
            {
                taglib_tag_set_year(metadataArray[i], yearLabels[i]->getText().getIntValue());
            }
        }
    }
}

void AudioFileTable::saveTableToTags()
{
    for(int i = 0; i < metadataFiles.size(); i++)
    {
        if(fileNamesToChangeWithTitle == true)
        {
            //Renames all the files to what their titles are specified as in the table
            //(*juceFiles)[i].moveFileTo(File(currentDirectoryPath + trackNameLabels[i]->getText() + fileExtension));
        }
    }
}

void AudioFileTable::actionListenerCallback(const String& message)
{
    if(message == "Apply Button Clicked")
    {
        if(int(batchControls.getButtonsActive()) != 0)
        {
            for(int i = 0; i < metadataArray.size(); i++)
            {
                if(selectionButtons[i]->getToggleState() == true)
                {
                    if(int(batchControls.getButtonsActive() & BatchRenameControls::titleButton) != 0)
                    {
                        //Removes characters set by the batch controls from the titles
                    trackNameLabels[i]->setText(trackNameLabels[i]->getText().replace(batchControls.getCharsToRemove(), ""), sendNotification);
                        
                        //Removes start chars set by batch controls from titles
                    trackNameLabels[i]->setText(trackNameLabels[i]->getText().substring(batchControls.getNumStartCharsToRemove()), sendNotification);
                       
                        //Removes end chars set by batch controls from titles
                    trackNameLabels[i]->setText(trackNameLabels[i]->getText().dropLastCharacters(batchControls.getNumEndCharsToRemove()), sendNotification);
                        
                        //Adds start chars set by batch controls from titles
                        trackNameLabels[i]->setText(trackNameLabels[i]->getText().replaceSection(0, 0, batchControls.getCharsToAddToStart()), sendNotification);
                        
                        //Adds chars to set position set by batch controls from titles
                        if(batchControls.getPositionToAdd() > trackNameLabels[i]->getText().length())
                        {
                            trackNameLabels[i]->setText(trackNameLabels[i]->getText() + batchControls.getCharsToAddToPosition(), sendNotification);
                        }
                        else
                        {
                        trackNameLabels[i]->setText(trackNameLabels[i]->getText().replaceSection(batchControls.getPositionToAdd(), 0, batchControls.getCharsToAddToPosition()), sendNotification);
                        }
                        
                        //Adds end chars set by batch controls from titles
                        trackNameLabels[i]->setText(trackNameLabels[i]->getText() + batchControls.getCharsToAddToEnd(), sendNotification);
                        
                        
                        //Replaces char with another char both set by batch controls for titles
                    trackNameLabels[i]->setText(trackNameLabels[i]->getText().replace(batchControls.getCharToReplace(), batchControls.getCharToReplaceWith()), sendNotification);
                    }
                
                    if(int(batchControls.getButtonsActive() & BatchRenameControls::artistButton) != 0)
                    {
                        //Removes characters set by the batch controls from the Artist names
                    artistNameLabels[i]->setText(artistNameLabels[i]->getText().replace(batchControls.getCharsToRemove(), ""), sendNotification);
                    
                        //Removes start chars set by batch controls from artist names
                    artistNameLabels[i]->setText(artistNameLabels[i]->getText().substring(batchControls.getNumStartCharsToRemove()), sendNotification);
                       
                        //Removes end chars set by batch controls from artist names
                    artistNameLabels[i]->setText(artistNameLabels[i]->getText().dropLastCharacters(batchControls.getNumEndCharsToRemove()), sendNotification);
                        
                        //Adds start chars set by batch controls from artist names
                        artistNameLabels[i]->setText(artistNameLabels[i]->getText().replaceSection(0, 0, batchControls.getCharsToAddToStart()), sendNotification);
                        
                        //Adds chars to set position set by batch controls from artist names
                        if(batchControls.getPositionToAdd() > artistNameLabels[i]->getText().length())
                        {
                            artistNameLabels[i]->setText(artistNameLabels[i]->getText() + batchControls.getCharsToAddToPosition(), sendNotification);
                        }
                        else
                        {
                            artistNameLabels[i]->setText(artistNameLabels[i]->getText().replaceSection(batchControls.getPositionToAdd(), 0, batchControls.getCharsToAddToPosition()), sendNotification);
                        }
                        
                        //Adds end chars set by batch controls from artist names
                        artistNameLabels[i]->setText(artistNameLabels[i]->getText() + batchControls.getCharsToAddToEnd(), sendNotification);
                        
                        //Replaces char with another char both set by batch controls for artist names
                    artistNameLabels[i]->setText(artistNameLabels[i]->getText().replace(batchControls.getCharToReplace(), batchControls.getCharToReplaceWith()), sendNotification);
                    }
                
                    if(int(batchControls.getButtonsActive() & BatchRenameControls::albumButton) != 0)
                    {
                        //Removes characters set by the batch controls from the album names
                    albumNameLabels[i]->setText(albumNameLabels[i]->getText().replace(batchControls.getCharsToRemove(), ""), sendNotification);
                        
                    
                        //Removes start chars set by batch controls from album names
                    albumNameLabels[i]->setText(albumNameLabels[i]->getText().substring(batchControls.getNumStartCharsToRemove()), sendNotification);
                       
                        //Removes end chars set by batch controls from album names
                    albumNameLabels[i]->setText(albumNameLabels[i]->getText().dropLastCharacters(batchControls.getNumEndCharsToRemove()), sendNotification);
                        
                        //Adds start chars set by batch controls from album names
                        albumNameLabels[i]->setText(albumNameLabels[i]->getText().replaceSection(0, 0, batchControls.getCharsToAddToStart()), sendNotification);
                        
                        //Adds chars to set position set by batch controls from album names
                        if(batchControls.getPositionToAdd() > albumNameLabels[i]->getText().length())
                        {
                            albumNameLabels[i]->setText(albumNameLabels[i]->getText() + batchControls.getCharsToAddToPosition(), sendNotification);
                        }
                        else
                        {
                            albumNameLabels[i]->setText(albumNameLabels[i]->getText().replaceSection(batchControls.getPositionToAdd(), 0, batchControls.getCharsToAddToPosition()), sendNotification);
                        }
                        
                        //Adds end chars set by batch controls from album names
                        albumNameLabels[i]->setText(albumNameLabels[i]->getText() + batchControls.getCharsToAddToEnd(), sendNotification);
                        
                        //Replaces char with another char both set by batch controls for album names
                    albumNameLabels[i]->setText(albumNameLabels[i]->getText().replace(batchControls.getCharToReplace(), batchControls.getCharToReplaceWith()), sendNotification);
                    }
                }
            }
            table.updateContent();
        }
    }
}
