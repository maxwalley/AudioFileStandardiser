/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

#define SUPPORTEDTYPES "*.mp3;*.flac;*.wav;*.wave;*.aac;*.wma;*.aiff"

//==============================================================================
MainComponent::MainComponent() : openSourceButton("Open Source"), chooser("Pick a folder", File(), "*.zip", true, false, nullptr), fileLoaded(false)
{
    setSize (300, 200);
    
    openSourceButton.addListener(this);
    addAndMakeVisible(openSourceButton);
    
    addAndMakeVisible(fileTable);
    
    manager.registerFormat(new MP3AudioFormat(), false);
    
    for(int i = 0; i < manager.getNumKnownFormats(); i++)
    {
        DBG(manager.getKnownFormat(i)->getFormatName());
    }
}

MainComponent::~MainComponent()
{
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
        setSize(650, fileTable.getTableHeight() + 30);
        fileTable.setBounds(0, 0, getWidth(), getHeight());
    }
}

void MainComponent::buttonClicked(Button* button)
{
    if(button == &openSourceButton)
    {
        //Looks and opens the file
        chooser.browseForMultipleFilesOrDirectories();
        
        if(chooser.getResult().exists() == true)
        {
            File file = chooser.getResult();
        
            if(file.existsAsFile() == true && file.getFileExtension() == ".zip")
            {
                //Creates a new directory
                String newDirectoryName(file.getParentDirectory().getFullPathName() + "/" + file.getFileName());
                newDirectoryName = newDirectoryName.dropLastCharacters(4);
                File newDirectory(newDirectoryName);
                newDirectory.createDirectory();
            
                //Decompresses the zip file
                ZipFile zip(chooser.getResult());
                zip.uncompressTo(newDirectory);
            
                if(newDirectory.getNumberOfChildFiles(2, SUPPORTEDTYPES) > 0)
                {
                    //Finds files in the new directory
                    currentFiles = newDirectory.findChildFiles(2, false, SUPPORTEDTYPES);
                    fileLoaded = true;
                    fileTable.setFiles(currentFiles);
                    resized();
                }
                else
                {
                    AlertWindow::showMessageBox(AlertWindow::WarningIcon, "No Suitable Files Detected", "The folder you have selected contains no supported file types");
                }
            }
            else if(file.isDirectory() == true)
            {
                if(file.getNumberOfChildFiles(2, SUPPORTEDTYPES) > 0)
                {
                    //Finds files in the new directory
                    currentFiles = file.findChildFiles(2, false, SUPPORTEDTYPES);
                    fileLoaded = true;
                    fileTable.setFiles(currentFiles);
                    resized();
                }
                else
                {
                    AlertWindow::showMessageBox(AlertWindow::WarningIcon, "No Suitable Files Detected", "The folder you have selected contains no supported file types");
                }
            }
        }
    }
}
