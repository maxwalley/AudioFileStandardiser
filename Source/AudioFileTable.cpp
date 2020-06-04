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


void TextEditorOutlineDrawer::drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& editor)
{
    Path path;
    
    path.startNewSubPath(width, 0);
    path.lineTo(width, height);
    path.lineTo(0, height);
    
    g.strokePath(path, PathStrokeType(1.0f));
}

//==============================================================================
AudioFileTable::AudioFileTable()    :   showBatchControls(false), fileLoaded(false)
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

    addAndMakeVisible(batchControlViewport);
    batchControlViewport.setVisible(false);
    batchControlViewport.setViewedComponent(&batchControls);
    
    batchControls.addActionListener(this);
}

AudioFileTable::~AudioFileTable()
{
    if(getIfFileLoaded())
    {
        //Clears the look and feels to prevent an error
        for(int i = 1; i < table.getHeader().getNumColumns(false); i++)
        {
            for(int j = 0; j < juceFiles.size()+1; j++)
            {
                table.getCellComponent(i, j)->setLookAndFeel(nullptr);
            }
        }
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
        batchControls.setSize(190, 860);
        batchControls.setVisible(true);
    }
}

bool AudioFileTable::setFiles()
{
    FileChooser chooser("Pick a folder", File(), "*.zip", true, false, nullptr);
    
    Array<File> lastArrayUsed;
    
    bool filesAreCurrentlyLoaded = false;
    
    if(juceFiles.size() != 0)
    {
        juceFiles.swapWith(lastArrayUsed);
        juceFiles.clear();
        metadataReaders.clear();
        filesAreCurrentlyLoaded = true;
    }
    
    //Looks and opens the file
    chooser.browseForMultipleFilesOrDirectories();
    
    if(chooser.getResult().exists() == true)
    {
        File file = chooser.getResult();
        
        if(file.existsAsFile())
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
                
                if(!filesAreCurrentlyLoaded)
                {
                    return false;
                }
                juceFiles.swapWith(lastArrayUsed);
                lastArrayUsed.clear();
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
                
                if(!filesAreCurrentlyLoaded)
                {
                    return false;
                }
                juceFiles.swapWith(lastArrayUsed);
                lastArrayUsed.clear();
            }
        }
    }
    
    for(int i = 0; i < juceFiles.size() + 1; i++)
    {
        if(i < juceFiles.size())
        {
            std::unique_ptr<FormatMetadataReader> currentReader = metadataManager.createMetadataReader(juceFiles.getReference(i));
                
            //If it = null pointer
            if(!currentReader)
            {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, "File Error", "The file: " + juceFiles[i].getFileName() + " does not use supported metadata and will not be included");
                
                juceFiles.remove(i);
                
                i--;
                
                if(juceFiles.size() == 0)
                {
                    AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Error - All files are incompatible", "None of the files in the selected folder have compatable metadata objects");
                    
                    juceFiles.clear();
                    
                    if(!filesAreCurrentlyLoaded)
                    {
                        return false;
                    }
                    //Resets i - Even though this will iterate through the loop again no errors should occur since any files with incompatible metadata types will have already been removed
                    i=-1;
                    juceFiles.swapWith(lastArrayUsed);
                    lastArrayUsed.clear();
                }
            }
            else
            {
                metadataReaders.add(currentReader.release());
            }
        }
    }
    
    batchControls.setDataSet(true);
    metadataReaders.sort(arraySorter);
    
    fileLoaded = true;
    
    //table.updateContent();
    
    return true;
}

int AudioFileTable::getTableHeight()
{
    return (metadataReaders.size() + 1)*table.getRowHeight()+table.getHeaderHeight();
}

void AudioFileTable::setFileNamesToChangeWithTitle(bool change)
{
    //fileNamesToChangeWithTitle = change;
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

bool AudioFileTable::getIfFileLoaded()
{
    return fileLoaded;
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
    g.drawLine(0, height, width, height);
}

void AudioFileTable::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    
}

Component* AudioFileTable::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    //If no component currently exists
    if(existingComponentToUpdate == nullptr)
    {
        if(columnId == 7)
        {
            TableToggleButtonComponent* componentToAdd = new TableToggleButtonComponent();
            componentToAdd->addListener(this);
            componentToAdd->setLocationInTable(columnId, rowNumber);
            //Sets the name for identification by a listener
            componentToAdd->setName("TableButton");
            return componentToAdd;
        }
        
        TableTextEditorComponent* componentToAdd = new TableTextEditorComponent();
        componentToAdd->addListener(this);
        componentToAdd->setLocationInTable(columnId, rowNumber);
        componentToAdd->setColour(TextEditor::textColourId, Colours::black);
        componentToAdd->setColour(TextEditor::outlineColourId, Colours::black);
        componentToAdd->setLookAndFeel(&drawer);
        
        if(rowNumber % 2 == 0)
        {
            componentToAdd->setColour(TextEditor::backgroundColourId, Colours::silver);
        }
        else
        {
            componentToAdd->setColour(TextEditor::backgroundColourId, Colours::lightgrey);
        }
        
        if(columnId == 1 || columnId == 5 || columnId == 6)
        {
            componentToAdd->setJustification(Justification::centred);
        }
        else
        {
            componentToAdd->setJustification(Justification::left);
        }
        
        if(columnId == 6)
        {
            componentToAdd->setEnabled(false);
        }
        
        return componentToAdd;
    }
    
    //If a component is already there
    
    //Selection buttons should not need updated once they are there
    if(columnId != 7)
    {
        //Casts the component to the table specific class
        TableTextEditorComponent* componentToUpdate = static_cast<TableTextEditorComponent*>(existingComponentToUpdate);
    
        if(rowNumber < juceFiles.size())
        {
            switch (columnId)
            {
                case 1:
                    componentToUpdate->setText(String(metadataReaders[rowNumber]->getTrackNum()), dontSendNotification);
                    break;
                    
                case 2:
                    componentToUpdate->setText(metadataReaders[rowNumber]->getTrackTitle(), dontSendNotification);
                    break;
                    
                case 3:
                    componentToUpdate->setText(metadataReaders[rowNumber]->getArtistName(), dontSendNotification);
                    break;
                    
                case 4:
                    componentToUpdate->setText(metadataReaders[rowNumber]->getAlbumName(), dontSendNotification);
                    break;
                    
                case 5:
                    componentToUpdate->setText(String(metadataReaders[rowNumber]->getYear()), dontSendNotification);
                    break;
                    
                case 6:
                    componentToUpdate->setText(metadataReaders[rowNumber]->getFileExtension(), dontSendNotification);
                    break;
                    
            }
            
            return componentToUpdate;
        }
    
        //If the label is in the last row
    
        bool comparatorFound = false;
        String comparatorString;
    
        for(int i = 0; i < metadataReaders.size() && comparatorFound != true; i++)
        {
            TableToggleButtonComponent* tempButton = static_cast<TableToggleButtonComponent*>(table.getCellComponent(7, i));
            TableTextEditorComponent* tempEditor = static_cast<TableTextEditorComponent*>(table.getCellComponent(columnId, i));
            
            if(tempButton->getToggleState() == true)
            {
                comparatorFound = true;
                comparatorString = tempEditor->getText();
            }
        }
    
        if(comparatorFound == true)
        {
            bool differenceFound = false;
        
            for(int i = 0; i < metadataReaders.size() && differenceFound != true; i++)
            {
                TableToggleButtonComponent* tempButton = static_cast<TableToggleButtonComponent*>(table.getCellComponent(7, i));
                TableTextEditorComponent* tempEditor = static_cast<TableTextEditorComponent*>(table.getCellComponent(columnId, i));
            
                if(tempButton->getToggleState() == true)
                {
                    if(tempEditor->getText().compare(comparatorString) != 0)
                    {
                        differenceFound = true;
                    }
                }
            }
            if(differenceFound == true)
            {
                //Dont send notification so it doesnt change all labels to "..."
                componentToUpdate->setText("...", dontSendNotification);
            }
            else
            {
                componentToUpdate->setText(comparatorString, dontSendNotification);
            }
        }
        else if(comparatorFound == false)
        {
            //Dont send notification so it doesnt change all labels to "..."
            componentToUpdate->setText("...", dontSendNotification);
        }
    
        return componentToUpdate;
    }
    
    return existingComponentToUpdate;
    
    
}

void AudioFileTable::buttonClicked(Button* button)
{
    //Checks to see if this is one of the buttons on the table
    if(button->getName().compare("TableButton") == 0)
    {
        //Casts the button into the special table button type
        TableToggleButtonComponent* tableButtonThatHasBeenClicked = static_cast<TableToggleButtonComponent*>(button);
        
        //Checks to see if the button thats been clicked is in the bottom row of the table
        if(tableButtonThatHasBeenClicked->getRowNumber() == juceFiles.size())
        {
            for(int i = 0; i < juceFiles.size(); i++)
            {
                //Changes all toggle states to the same as the button in the last row
                TableToggleButtonComponent* tempButton = static_cast<TableToggleButtonComponent*>(table.getCellComponent(7, i));
                tempButton->setToggleState(tableButtonThatHasBeenClicked->getToggleState(), sendNotification);
            }
        }
        //If its any other button
        else
        {
            //Updates the table to check for comparators
            table.updateContent();
        }
    }
    
    /*else if(button == &changeLocationButton)
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
    }*/
}

void AudioFileTable::textEditorTextChanged(TextEditor& editor)
{
    //Casts the editor to one of the specific table component editors so that row num and col id can be accessed
    TableTextEditorComponent& editorThatHasChanged = static_cast<TableTextEditorComponent&>(editor);
    
    //If the editor is not in the bottom row of the table
    if(editorThatHasChanged.getRowNumber() != juceFiles.size())
    {
        changeMetadataForCellComponent(editorThatHasChanged.getColumnID(), editorThatHasChanged.getRowNumber(), editorThatHasChanged.getText());
    }
    
    //If label is from the bottom row
    else
    {
        //Iterates through the rows
        for(int i = 0; i < metadataReaders.size(); i++)
        {
            //Gets the button for this row and the editor for the row and column
            TableToggleButtonComponent* tempButton = static_cast<TableToggleButtonComponent*>(table.getCellComponent(7, i));
            
            //If the row is selected with the toggle buttons the editor in that rows colun will be changed
            if(tempButton->getToggleState())
            {
                changeMetadataForCellComponent(editorThatHasChanged.getColumnID(), i, editorThatHasChanged.getText());
            }
        }
        table.updateContent();
    }
}

void AudioFileTable::actionListenerCallback(const String& message)
{
    if(message == "Apply Button Clicked")
    {
        if(int(batchControls.getButtonsActive()) != 0)
        {
            for(int j = 0; j < 3; j++)
            {
                int comparator = 0;
                int column = 0;
                
                switch (j)
                {
                    case 0:
                        comparator = int(batchControls.getButtonsActive() & BatchRenameControls::titleButton);
                        column = 2;
                        break;
                        
                    case 1:
                        comparator = int(batchControls.getButtonsActive() & BatchRenameControls::artistButton);
                        column = 3;
                        break;
                        
                    case 2:
                        comparator = int(batchControls.getButtonsActive() & BatchRenameControls::albumButton);
                        column = 4;
                        break;
                }
                
                if(comparator != 0)
                {
                    for(int i = 0; i < metadataReaders.size(); i++)
                    {
                        //Gets the button for this row
                        TableToggleButtonComponent* tempButton = static_cast<TableToggleButtonComponent*>(table.getCellComponent(7, i));
                        
                        if(tempButton->getToggleState() == true)
                        {
                            //Gets the editor for this row and column
                            TableTextEditorComponent* tempEditor = static_cast<TableTextEditorComponent*>(table.getCellComponent(column, i));
                            
                            //Gets the text from the editor that is currently being changed
                            String textToReplace = tempEditor->getText();
                            
                            if(batchControls.getCharsToRemove().isNotEmpty())
                             {
                                 //Removes characters set by the batch controls
                                 textToReplace = textToReplace.replace(batchControls.getCharsToRemove(), "");
                             }
                             
                             if(batchControls.getNumStartCharsToRemove() != 0)
                             {
                                 //Removes start chars set by batch controls from titles
                                 textToReplace = textToReplace.substring(batchControls.getNumStartCharsToRemove());
                             }
                            
                             if(batchControls.getNumEndCharsToRemove() != 0)
                             {
                                 //Removes end chars set by batch controls from titles
                                 textToReplace = textToReplace.dropLastCharacters(batchControls.getNumEndCharsToRemove());
                             }
                                 
                             if(batchControls.getCharsToAddToStart().isNotEmpty())
                             {
                                 //Adds start chars set by batch controls from titles
                                 textToReplace = textToReplace.replaceSection(0, 0, batchControls.getCharsToAddToStart());
                             }
                             
                             if(batchControls.getCharsToAddToPosition().isNotEmpty())
                             {
                                 //Adds chars to set position set by batch controls from titles
                                 if(batchControls.getPositionToAdd() > tempEditor->getText().length())
                                 {
                                     textToReplace = textToReplace + batchControls.getCharsToAddToPosition();
                                 }
                                 else
                                 {
                                     textToReplace = textToReplace.replaceSection(batchControls.getPositionToAdd(), 0, batchControls.getCharsToAddToPosition());
                                 }
                             }
                             
                             if(batchControls.getCharsToAddToEnd().isNotEmpty())
                             {
                                 //Adds end chars set by batch controls from titles
                                 textToReplace = textToReplace + batchControls.getCharsToAddToEnd();
                             }
                             
                             if(batchControls.getCharToReplace().isNotEmpty())
                             {
                                 //Replaces char with another char both set by batch controls for titles
                                 textToReplace = textToReplace.replace(batchControls.getCharToReplace(), batchControls.getCharToReplaceWith());
                             }
                             
                             //Checks if the default capatalisation settings in batch control is set. If not it'll check the state of the other batch control settings
                             if(batchControls.getDefaultCapSettings())
                             {
                                 //Brings all text to lower case
                                 textToReplace = textToReplace.toLowerCase();
                            
                                 //Capatalises all first letters of the text
                                 textToReplace = StringChecker::capatalizeFirstLetters(textToReplace);
                            
                                 //Removes capitals from all the correct words
                                 textToReplace = StringChecker::decapatalizeWords(textToReplace);
                             }
                             else
                             {
                                 //Capatalises or decapatalises all words based on what is toggled in batch controls
                                 if(batchControls.getCapAllWords())
                                 {
                                     textToReplace = textToReplace.toUpperCase();
                                 }
                                 
                                 else if(batchControls.getDecapAllWords())
                                 {
                                     textToReplace = textToReplace.toLowerCase();
                                 }
                                 
                                 if(batchControls.getCapWord().isNotEmpty())
                                 {
                                     //Capatalises a certain word set by batch controls
                                     textToReplace = textToReplace.replace(batchControls.getCapWord(), batchControls.getCapWord().toUpperCase());
                                 }
                                 
                                 //Capatalises the start of all words or just one specific one based on the options set by batch controls
                                 if(batchControls.getCapStartOfAllWords() == true)
                                 {
                                     textToReplace = StringChecker::capatalizeFirstLetters(textToReplace);
                                 }
                                 //Just one word
                                 else if(batchControls.getCapStartOfWord().isNotEmpty())
                                 {
                                     textToReplace = textToReplace.replace(batchControls.getCapStartOfWord(), StringChecker::capatalizeFirstLetters(batchControls.getCapStartOfWord()));
                                 }
                                 
                                 changeMetadataForCellComponent(column, i, textToReplace);
                             }
                        }
                    }
                }
            }
        }
        table.updateContent();
    }
}

void AudioFileTable::changeMetadataForCellComponent(int cellColumn, int row, String newData)
{
    switch (cellColumn)
    {
        case 1:
            metadataReaders[row]->setTrackNum(newData.getIntValue());
            break;
            
        case 2:
            metadataReaders[row]->setTrackTitle(newData);
            break;
            
        case 3:
            metadataReaders[row]->setArtistName(newData);
            break;
            
        case 4:
            metadataReaders[row]->setAlbumName(newData);
            break;
            
        case 5:
            metadataReaders[row]->setYear(newData.getIntValue());
            break;
    }
}
