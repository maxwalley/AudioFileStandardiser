/*
  ==============================================================================

    AudioFileTable.cpp
    Created: 2 May 2020 5:25:10pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioFileTable.h"

#define SUPPORTEDTYPES "*.mp3;*.flac;*.wav;*.wave;*.aac;*.wma;*.aif;*.m4a"

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

int MetadataReaderSorter::compareElements(FormatMetadataReader* first, FormatMetadataReader* second)
{
    if(first->getTrackNum() > second->getTrackNum())
    {
        return 1;
    }
    else if(first->getTrackNum() == second->getTrackNum())
    {
        return 0;
    }
    else if(first->getTrackNum() < second->getTrackNum())
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
        batchControls.setSize(190, 860);
        batchControls.setVisible(true);
    }
    
    correctDataButton.setBounds(0, getTableHeight(), 200, 30);
    saveButton.setBounds(200, getTableHeight(), 200, 30);
    changeLocationButton.setBounds(400, getTableHeight(), 200, 30);
}

bool AudioFileTable::setFiles()
{
    FileChooser chooser("Pick a folder", File(), "*.zip", true, false, nullptr);
    
    //Looks and opens the file
    chooser.browseForMultipleFilesOrDirectories();
    
    if(chooser.getResult().exists() == true)
    {
        File file = chooser.getResult();
        
    
        if(file.existsAsFile() && file.getFileExtension() == ".zip")
        {
            //Creates a new directory
            String newDirectoryName(file.getParentDirectory().getFullPathName() + "/" + file.getFileNameWithoutExtension());
            File newDirectory(newDirectoryName);
            newDirectory.createDirectory();
        
            //Decompresses the zip file
            ZipFile zip(chooser.getResult());
            zip.uncompressTo(newDirectory);
        
            if(newDirectory.getNumberOfChildFiles(2, SUPPORTEDTYPES) > 0)
            {
                //Finds files in the new directory
                juceFiles = newDirectory.findChildFiles(2, false, SUPPORTEDTYPES);
            }
            else
            {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, "No Suitable Files Detected", "The folder you have selected contains no supported file types");
                return false;
            }
        }
        
        else if(file.isDirectory() == true)
        {
            if(file.getNumberOfChildFiles(2, SUPPORTEDTYPES) > 0)
            {
                //Finds files in the new directory
                juceFiles = file.findChildFiles(2, false, SUPPORTEDTYPES);
            }
            else
            {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, "No Suitable Files Detected", "The folder you have selected contains no supported file types");
                return false;
            }
        }
    }
    
    metadataArray.ensureStorageAllocated(juceFiles.size());
    
    for(int i = 0; i < juceFiles.size() + 1; i++)
    {
        bool entryIsInvalid;
        
        if(i < juceFiles.size())
        {
            std::unique_ptr<FormatMetadataReader> tempReader = metadataManager.createMetadataReader(juceFiles.getReference(i));
                
            if(tempReader == nullptr)
            {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, "File Error", "The file: " + juceFiles[i].getFileName() + " does not use supported metadata and will not be included");
                
                juceFiles.remove(i);
                entryIsInvalid = true;
                
                i--;
                DBG("Size" << juceFiles.size());
                if(juceFiles.size() == 0)
                {
                    AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Error - All files are incompatible", "None of the files in the selected folder have compatable metadata objects");
                    return false;
                }
            }
            else
            {
                metadataReaders.add(metadataManager.createMetadataReader(juceFiles.getReference(i)));
                entryIsInvalid = false;
            }
        }
        
        if(entryIsInvalid == false)
        {
            trackNumLabels.add(new Label);
            trackNumLabels[i]->setName("Track Num Label " + String(i));
            trackNumLabels[i]->setEditable(true);
            trackNumLabels[i]->setColour(Label::textColourId, Colours::black);
            trackNumLabels[i]->setJustificationType(Justification::centred);
            trackNumLabels[i]->addListener(this);
        
            trackNameLabels.add(new Label);
            trackNameLabels[i]->setName("Track Name Label " + String(i));
            trackNameLabels[i]->setEditable(true);
            trackNameLabels[i]->setColour(Label::textColourId, Colours::black);
            trackNameLabels[i]->addListener(this);
        
            artistNameLabels.add(new Label);
            artistNameLabels[i]->setName("Artist Name Label " + String(i));
            artistNameLabels[i]->setEditable(true);
            artistNameLabels[i]->setColour(Label::textColourId, Colours::black);
            artistNameLabels[i]->addListener(this);
        
            albumNameLabels.add(new Label);
            albumNameLabels[i]->setName("Album Name Label " + String(i));
            albumNameLabels[i]->setEditable(true);
            albumNameLabels[i]->setColour(Label::textColourId, Colours::black);
            albumNameLabels[i]->addListener(this);
        
            yearLabels.add(new Label);
            yearLabels[i]->setName("Year Label " + String(i));
            yearLabels[i]->setEditable(true);
            yearLabels[i]->setColour(Label::textColourId, Colours::black);
            yearLabels[i]->addListener(this);
        
            selectionButtons.add(new ToggleButton);
            selectionButtons[i]->addListener(this);
        }
    }
    
    batchControls.setDataSet(true);
    metadataReaders.sort(arraySorter);
       
    //Make this better
    fileExtension = juceFiles[0].getFileExtension();
       
    table.updateContent();
    
    return true;
}

void AudioFileTable::refreshTable()
{
    table.updateContent();
}

int AudioFileTable::getTableHeight()
{
    return (metadataReaders.size() + 1)*table.getRowHeight()+table.getHeaderHeight();
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
    if(metadataReaders.size() > 0)
    {
        return metadataReaders.size() + 1;
    }
    return 0;
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
        if(rowNumber == metadataReaders.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataReaders.size() && comparatorFound != true; i++)
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
                
                for(int i = 0; i < metadataReaders.size() && differenceFound != true; i++)
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
            trackNumLabels[rowNumber]->setText(String(metadataReaders[rowNumber]->getTrackNum()), sendNotification);
        }
        return trackNumLabels[rowNumber];
    }
    
    else if(columnId == 2)
    {
        if(rowNumber == metadataReaders.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataReaders.size() && comparatorFound != true; i++)
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
                
                for(int i = 0; i < metadataReaders.size() && differenceFound != true; i++)
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
            trackNameLabels[rowNumber]->setText(metadataReaders[rowNumber]->getTrackTitle(), sendNotification);
        }
        return trackNameLabels[rowNumber];
    }
    
    else if(columnId == 3)
    {
        if(rowNumber == metadataReaders.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataReaders.size() && comparatorFound != true; i++)
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
                
                for(int i = 0; i < metadataReaders.size() && differenceFound != true; i++)
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
            artistNameLabels[rowNumber]->setText(metadataReaders[rowNumber]->getArtistName(), sendNotification);
        }
        return artistNameLabels[rowNumber];
    }
    
    else if(columnId == 4)
    {
        if(rowNumber == metadataReaders.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataReaders.size() && comparatorFound != true; i++)
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
                
                for(int i = 0; i < metadataReaders.size() && differenceFound != true; i++)
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
             albumNameLabels[rowNumber]->setText(metadataReaders[rowNumber]->getAlbumName(), sendNotification);
        }
        return albumNameLabels[rowNumber];
    }
    
    else if(columnId == 5)
    {
        if(rowNumber == metadataReaders.size())
        {
            bool comparatorFound = false;
            String comparatorString;
            
            for(int i = 0; i < metadataReaders.size() && comparatorFound != true; i++)
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
                
                for(int i = 0; i < metadataReaders.size() && differenceFound != true; i++)
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
            yearLabels[rowNumber]->setText(String(metadataReaders[rowNumber]->getYear()), sendNotification);
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
        for(int i = 0; i < metadataArray.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                trackNameLabels[i]->setText(StringChecker::decapatalizeWords(trackNameLabels[i]->getText()), sendNotification);
                albumNameLabels[i]->setText(StringChecker::decapatalizeWords(albumNameLabels[i]->getText()), sendNotification);
                artistNameLabels[i]->setText(StringChecker::decapatalizeWords(artistNameLabels[i]->getText()), sendNotification);
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

        if(chooser.browseForDirectory())
        {
            for(int i = 0; i < metadataReaders.size(); i++)
            {
                String newDirectoryPath = chooser.getResult().getFullPathName() + "/" + metadataReaders[i]->getFileName();
                
                metadataReaders[i]->moveFile(newDirectoryPath);
            }
        }
    }
    
    else if(button == selectionButtons[metadataReaders.size()])
    {
        for(int i = 0; i < metadataReaders.size(); i++)
        {
            selectionButtons[i]->setToggleState(selectionButtons[metadataReaders.size()]->getToggleState(), sendNotification);
            table.updateContent();
        }
    }
    else
    {
        for(int i = 0; i < metadataReaders.size(); i++)
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
    if(label == trackNumLabels[metadataReaders.size()])
    {
        for(int i = 0; i < metadataReaders.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                trackNumLabels[i]->setText(trackNumLabels[metadataReaders.size()]->getText(), sendNotification);
            }
        }
    }
    
    //The change all label for the track name field
    else if(label == trackNameLabels[metadataReaders.size()])
    {
        for(int i = 0; i < metadataReaders.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                //Sends a notification to make the relevent changes to the readers
                trackNameLabels[i]->setText(trackNameLabels[metadataReaders.size()]->getText(), sendNotification);
            }
        }
    }
    
    //The change all label for the artist name field
    else if(label == artistNameLabels[metadataReaders.size()])
    {
        for(int i = 0; i < metadataReaders.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                artistNameLabels[i]->setText(artistNameLabels[metadataReaders.size()]->getText(), sendNotification);
            }
        }
    }
    
    //The change all label for the album name field
    else if(label == albumNameLabels[metadataReaders.size()])
    {
        for(int i = 0; i < metadataReaders.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                albumNameLabels[i]->setText(albumNameLabels[metadataReaders.size()]->getText(), sendNotification);
            }
        }
    }
    
    //The change all label for the year field
    else if(label == yearLabels[metadataReaders.size()])
    {
        for(int i = 0; i < metadataReaders.size(); i++)
        {
            if(selectionButtons[i]->getToggleState() == true)
            {
                yearLabels[i]->setText(yearLabels[metadataReaders.size()]->getText(), sendNotification);
            }
        }
    }
    
    else
    {
        //Runs through the arrays and checks to find the label. Then writes into the metadata reader
        for(int i = 0; i < metadataReaders.size(); i++)
        {
            if(label == trackNumLabels[i])
            {
                metadataReaders[i]->setTrackNum(trackNumLabels[i]->getText().getIntValue());
            }
            else if(label == trackNameLabels[i])
            {
                metadataReaders[i]->setTrackTitle(trackNameLabels[i]->getText());
                
                if(fileNamesToChangeWithTitle == true)
                {
                    String newDirectory = metadataReaders[i]->getFileLocation().replace(metadataReaders[i]->getFileNameWithoutExtension(), trackNameLabels[i]->getText());
                    
                    metadataReaders[i]->moveFile(newDirectory);
                }
            }
            else if(label == artistNameLabels[i])
            {
                metadataReaders[i]->setArtistName(artistNameLabels[i]->getText());
            }
            else if(label == albumNameLabels[i])
            {
                metadataReaders[i]->setAlbumName(albumNameLabels[i]->getText());
            }
            else if(label == yearLabels[i])
            {
                metadataReaders[i]->setYear(yearLabels[i]->getText().getIntValue());
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
            for(int i = 0; i < metadataReaders.size(); i++)
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
                        
                        //Checks if the default capatalisation settings in batch control is set. If not it'll check the state of the other batch control settings
                        if(batchControls.getDefaultCapSettings())
                        {
                            //Brings all text to lower case
                            trackNameLabels[i]->setText(trackNameLabels[i]->getText().toLowerCase(), dontSendNotification);
                       
                            //Capatalises all first letters of the text
                        trackNameLabels[i]->setText(StringChecker::capatalizeFirstLetters(trackNameLabels[i]->getText()), dontSendNotification);
                       
                            //Removes capitals from all the correct words
                        trackNameLabels[i]->setText(StringChecker::decapatalizeWords(trackNameLabels[i]->getText()), sendNotification);
                        }
                        else
                        {
                            //Capatalises or decapatalises all words based on what is toggled in batch controls
                            if(batchControls.getCapAllWords())
                            {
                                trackNameLabels[i]->setText(trackNameLabels[i]->getText().toUpperCase(), sendNotification);
                            }
                            
                            else if(batchControls.getDecapAllWords())
                            {
                                trackNameLabels[i]->setText(trackNameLabels[i]->getText().toLowerCase(), sendNotification);
                            }
                            
                           //Capatalises a certain word set by batch controls
                            trackNameLabels[i]->setText(trackNameLabels[i]->getText().replace(batchControls.getCapWord(), batchControls.getCapWord().toUpperCase()), sendNotification);
                            
                            //Capatalises the start of all words or just one specific one based on the options set by batch controls
                            if(batchControls.getCapStartOfAllWords() == true)
                           
                            {   trackNameLabels[i]->setText(StringChecker::capatalizeFirstLetters(trackNameLabels[i]->getText()), sendNotification);
                            }
                            //Just one word
                            else if(!batchControls.getCapStartOfWord().isEmpty())
                            {
                                trackNameLabels[i]->setText(trackNameLabels[i]->getText().replace(batchControls.getCapStartOfWord(), StringChecker::capatalizeFirstLetters(batchControls.getCapStartOfWord())), sendNotification);
                            }
                        }
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
                        
                        //Checks if the default capatalisation settings in batch control is set. If not it'll check the state of the other batch control settings
                         if(batchControls.getDefaultCapSettings())
                         {
                             //Brings all text to lower case
                             artistNameLabels[i]->setText(artistNameLabels[i]->getText().toLowerCase(), dontSendNotification);
                        
                             //Capatalises all first letters of the text
                         artistNameLabels[i]->setText(StringChecker::capatalizeFirstLetters(artistNameLabels[i]->getText()), dontSendNotification);
                        
                             //Removes capitals from all the correct words
                         artistNameLabels[i]->setText(StringChecker::decapatalizeWords(artistNameLabels[i]->getText()), sendNotification);
                         }
                         else
                         {
                             //Capatalises or decapatalises all words based on what is toggled in batch controls
                             if(batchControls.getCapAllWords())
                             {
                                 artistNameLabels[i]->setText(artistNameLabels[i]->getText().toUpperCase(), sendNotification);
                             }
                             
                             else if(batchControls.getDecapAllWords())
                             {
                                 artistNameLabels[i]->setText(artistNameLabels[i]->getText().toLowerCase(), sendNotification);
                             }
                             
                            //Capatalises a certain word set by batch controls
                             artistNameLabels[i]->setText(artistNameLabels[i]->getText().replace(batchControls.getCapWord(), batchControls.getCapWord().toUpperCase()), sendNotification);
                             
                             //Capatalises the start of all words or just one specific one based on the options set by batch controls
                             if(batchControls.getCapStartOfAllWords() == true)
                            
                             {   artistNameLabels[i]->setText(StringChecker::capatalizeFirstLetters(artistNameLabels[i]->getText()), sendNotification);
                             }
                             //Just one word
                             else if(!batchControls.getCapStartOfWord().isEmpty())
                             {
                                 artistNameLabels[i]->setText(artistNameLabels[i]->getText().replace(batchControls.getCapStartOfWord(), StringChecker::capatalizeFirstLetters(batchControls.getCapStartOfWord())), sendNotification);
                             }
                         }
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
                        
                        //Checks if the default capatalisation settings in batch control is set. If not it'll check the state of the other batch control settings
                         if(batchControls.getDefaultCapSettings())
                         {
                             //Brings all text to lower case
                             albumNameLabels[i]->setText(albumNameLabels[i]->getText().toLowerCase(), dontSendNotification);
                        
                             //Capatalises all first letters of the text
                             albumNameLabels[i]->setText(StringChecker::capatalizeFirstLetters(albumNameLabels[i]->getText()), dontSendNotification);
                        
                             //Removes capitals from all the correct words
                         albumNameLabels[i]->setText(StringChecker::decapatalizeWords(albumNameLabels[i]->getText()), sendNotification);
                         }
                         else
                         {
                             //Capatalises or decapatalises all words based on what is toggled in batch controls
                             if(batchControls.getCapAllWords())
                             {
                                 albumNameLabels[i]->setText(albumNameLabels[i]->getText().toUpperCase(), sendNotification);
                             }
                             
                             else if(batchControls.getDecapAllWords())
                             {
                                 albumNameLabels[i]->setText(albumNameLabels[i]->getText().toLowerCase(), sendNotification);
                             }
                             
                            //Capatalises a certain word set by batch controls
                             albumNameLabels[i]->setText(albumNameLabels[i]->getText().replace(batchControls.getCapWord(), batchControls.getCapWord().toUpperCase()), sendNotification);
                             
                             //Capatalises the start of all words or just one specific one based on the options set by batch controls
                             if(batchControls.getCapStartOfAllWords() == true)
                            
                             {   albumNameLabels[i]->setText(StringChecker::capatalizeFirstLetters(albumNameLabels[i]->getText()), sendNotification);
                             }
                             //Just one word
                             else if(!batchControls.getCapStartOfWord().isEmpty())
                             {
                                 albumNameLabels[i]->setText(albumNameLabels[i]->getText().replace(batchControls.getCapStartOfWord(), StringChecker::capatalizeFirstLetters(batchControls.getCapStartOfWord())), sendNotification);
                             }
                         }
                    }
                }
            }
            
            table.updateContent();
        }
    }
}
