/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : openSourceButton("Open Source"), fileLoaded(false), fileNamesToChangeWithTitle(true), batchControlsShown(false)
{
    setSize (300, 200);
    
    openSourceButton.addListener(this);
    addAndMakeVisible(openSourceButton);
    
    addAndMakeVisible(fileTable);
    fileTable.addBatchControlsActionListener(this);
    fileTable.setName("File Table");
    
    setMacMainMenu(this);
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
    if(fileLoaded == false)
    {
        openSourceButton.setBounds(100, 60, 100, 30);
    }
    else if(fileLoaded == true)
    {
        if(batchControlsShown == false)
        {
            setSize(650, fileTable.getTableHeight() + 30);
        }
        else
        {
            setSize(850, fileTable.getTableHeight() + 30);
        }
        fileTable.setBounds(0, 0, getWidth(), getHeight());
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
    StringArray menuNames("Settings", "View", "Files");
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
    }
    
    else if(topLevelMenuIndex == 2)
    {
        menu.addItem(1, "Change files", true, false);
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
            batchControlsShown = !batchControlsShown;
            resized();
            fileTable.setBatchControlsVisible(batchControlsShown);
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
    if(message == "Close Button Clicked")
    {
        batchControlsShown = false;
        resized();
        fileTable.setBatchControlsVisible(batchControlsShown);
        menuItemsChanged();
    }
}
