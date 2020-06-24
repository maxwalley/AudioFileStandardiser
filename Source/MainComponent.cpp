/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : openSourceButton("Open Source"), fileLoaded(false), fileNamesToChangeWithTitle(false), batchControlsShown(false), fileAndFolderControlsShown(false)
{
    setSize (300, 200);
    setName("Main Component");
    
    openSourceButton.addListener(this);
    addAndMakeVisible(openSourceButton);
    
    addAndMakeVisible(fileTable);
    fileTable.addExtraInfoActionListener(this);
    fileTable.setName("File Table");
    fileTable.addActionListener(this);
    
    setMacMainMenu(this);
    
    DataHandler testHandler;
    std::vector<AudioMetadataReader*> testVector;
    AudioMetadataManager manager;
    
    std::unique_ptr<AudioMetadataReader> testReader = manager.createMetadataReader(File("/Users/maxwalley/Desktop/Childish Gambino - 3.15.20/03.Time.mp3"));
    
    std::unique_ptr<AudioMetadataReader> testReader2 = manager.createMetadataReader(File("/Users/maxwalley/Desktop/Childish Gambino - 3.15.20/01.0.00.mp3"));
    
    testVector.push_back(testReader.release());
    
    testHandler.addData(testVector);
    
    testHandler.addData(testReader2.release());
    
    for(int i = 0; i < testHandler.numEntries(); i++)
    {
        DBG(testHandler.getDataForItem(DataHandler::artistName, i));
    }
    
}
    
MainComponent::~MainComponent()
{
    setMacMainMenu(0);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    
}

void MainComponent::resized()
{
    if(!fileTable.getIfFileLoaded())
    {
        openSourceButton.setBounds(100, 60, 100, 30);
    }
    else
    {
        setSize(fileTable.getWidth(), fileTable.getHeight());
    }
}

void MainComponent::buttonClicked(Button* button)
{
    if(button == &openSourceButton)
    {
        if(fileTable.setFiles())
        {
            fileLoaded = true;
            resized();
        }
    }
}

StringArray MainComponent::getMenuBarNames()
{
    StringArray menuNames;
    
    menuNames.ensureStorageAllocated(3);
    
    menuNames.insert(0, "Settings");
    menuNames.insert(2, "Files");
    
    if(fileTable.getIfFileLoaded())
    {
        menuNames.insert(1, "View");
    }
    return menuNames;
}

PopupMenu MainComponent::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
    PopupMenu menu;
    
    //Settings Menu
     if(topLevelMenuIndex == 0)
    {
        menu.addItem(1, "Change Filenames to Title", true, fileNamesToChangeWithTitle);
    }
    
    //View Menu
    else if(topLevelMenuIndex == 1)
    {
        menu.addItem(1, "Show Batch Controls", true, batchControlsShown);
        menu.addItem(2, "Show File/Directory Controls", true, fileAndFolderControlsShown);
    }
    
    else if(topLevelMenuIndex == 2)
    {
        menu.addItem(1, "Select New Source", true, false);
    }
    
    return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    //Settings Menu
    if(topLevelMenuIndex == 0)
    {
        //Change Filenames to Title
        if(menuItemID == 1)
        {
            //Inverses the bool
            fileNamesToChangeWithTitle = !fileNamesToChangeWithTitle;
            fileTable.setFileNamesToChangeWithTitle(fileNamesToChangeWithTitle);
            menuItemsChanged();
        }
    }
    
    //View Menu
    else if(topLevelMenuIndex == 1)
    {
        //Show Batch Controls
        if(menuItemID == 1)
        {
            fileAndFolderControlsShown = false;
            fileTable.setFileAndDirectoryControlsVisible(fileAndFolderControlsShown);
            batchControlsShown = !batchControlsShown;
            fileTable.setBatchControlsVisible(batchControlsShown);
            resized();
            menuItemsChanged();
        }
        
        //Show File/Folder Controls
        else if(menuItemID == 2)
        {
            batchControlsShown = false;
            fileTable.setBatchControlsVisible(batchControlsShown);
            fileAndFolderControlsShown = !fileAndFolderControlsShown;
            fileTable.setFileAndDirectoryControlsVisible(fileAndFolderControlsShown);
            resized();
            menuItemsChanged();
        }
    }
    
    //Files menu
    else if(topLevelMenuIndex == 2)
    {
        if(menuItemID == 1)
        {
            if(fileTable.setFiles())
            {
                fileLoaded = true;
                resized();
            }
        }
    }
}

void MainComponent::actionListenerCallback(const String& message)
{
    if(message == "Extra Info Close Button Clicked")
    {
        /*batchControlsShown = false;
        fileAndFolderControlsShown = false;
        resized();
        fileTable.setBatchControlsVisible(batchControlsShown);
        fileTable.setFileAndDirectoryControlsVisible(fileAndFolderControlsShown);*/
        menuItemsChanged();
    }
    
    else if(message == "Resize")
    {
        resized();
    }
}
