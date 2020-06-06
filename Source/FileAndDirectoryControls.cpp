/*
  ==============================================================================

    FileAndDirectoryControls.cpp
    Created: 4 Jun 2020 5:06:31pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileAndDirectoryControls.h"

//==============================================================================
FileAndDirectoryControls::FileAndDirectoryControls()    :   dataSet(false), changeDirectoryButton("Select New Directory"), moveButton("Move Files")
{
    addAndMakeVisible(currentDirectoryLabel);
    currentDirectoryLabel.setText("Selected Files Directory", dontSendNotification);
    addAndMakeVisible(currentDirectoryEditor);
    
    addAndMakeVisible(changeDirectoryButton);
    
    addAndMakeVisible(folderHierachyLabel);
    folderHierachyLabel.setText("Set Folder Hierachy Wildcards", dontSendNotification);
    addAndMakeVisible(folderHierachyEditor);
    
    addAndMakeVisible(moveButton);
}

FileAndDirectoryControls::~FileAndDirectoryControls()
{
}

void FileAndDirectoryControls::paint (Graphics& g)
{
    if(dataSet)
    {
        g.setColour(Colours::white);
        g.setFont(Font(20));
        g.drawText("File and Directory", 0, 5, getWidth(), 30, Justification::centred);
    }
}

void FileAndDirectoryControls::resized()
{
    if(dataSet)
    {
        currentDirectoryLabel.setBounds(0, 40, getWidth(), 20);
        currentDirectoryEditor.setBounds(5, 65, getWidth()-10, 50);
        
        changeDirectoryButton.setBounds(5, 120, getWidth()-10, 30);
        
        folderHierachyLabel.setBounds(0, 170, getWidth(), 20);
        folderHierachyEditor.setBounds(5, 195, getWidth()-10, 30);
        
        moveButton.setBounds(5, 245, getWidth()-10, 30);
    }
}

void FileAndDirectoryControls::setDataSet(bool isDataSet)
{
    dataSet = isDataSet;
}

void FileAndDirectoryControls::setCurrentDirectory(String newDirectory)
{
    currentDirectoryEditor.setText(newDirectory, dontSendNotification);
}

String FileAndDirectoryControls::getCurrentDirectoryDisplayed() const
{
    return currentDirectoryEditor.getText();
}

void FileAndDirectoryControls::buttonClicked(Button* button)
{
    FileChooser chooser("Select New Directory");
    
    if(chooser.browseForDirectory())
    {
        File newDirectory = chooser.getResult();
        
        currentDirectoryEditor.setText(newDirectory.getFullPathName(), sendNotification);
    }
}
