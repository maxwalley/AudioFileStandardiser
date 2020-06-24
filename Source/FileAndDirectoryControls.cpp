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
FileAndDirectoryControls::FileAndDirectoryControls()    :   dataSet(false), changeDirectoryButton("Select New Directory"), moveButton("Move Files"), closeButton("Close")
{
    addAndMakeVisible(currentDirectoryLabel);
    currentDirectoryLabel.setText("Selected Files Directory", dontSendNotification);
    addAndMakeVisible(currentDirectoryDataLabel);
    currentDirectoryDataLabel.setEditable(false);
    currentDirectoryDataLabel.setColour(Label::backgroundColourId, Colour(37, 50, 55));
    currentDirectoryDataLabel.setColour(Label::outlineColourId, Colour(141, 152, 155));
    
    addAndMakeVisible(changeDirectoryButton);
    changeDirectoryButton.addListener(this);
    
    addAndMakeVisible(folderHierachyLabel);
    folderHierachyLabel.setText("Set Folder Hierachy Wildcards", dontSendNotification);
    addAndMakeVisible(folderHierachyEditor);
    
    addAndMakeVisible(moveButton);
    moveButton.addListener(this);
    
    addAndMakeVisible(closeButton);
    closeButton.addListener(this);
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
        currentDirectoryDataLabel.setBounds(5, 65, getWidth()-10, 50);
        
        changeDirectoryButton.setBounds(5, 120, getWidth()-10, 30);
        
        folderHierachyLabel.setBounds(0, 170, getWidth(), 20);
        folderHierachyEditor.setBounds(5, 195, getWidth()-10, 30);
        
        moveButton.setBounds(5, 245, getWidth()-10, 30);
        
        closeButton.setBounds(5, 285, getWidth()-10, 30);
    }
}

void FileAndDirectoryControls::setDataSet(bool isDataSet)
{
    dataSet = isDataSet;
}

void FileAndDirectoryControls::setCurrentDirectory(const String& newDirectory)
{
    currentDirectoryDataLabel.setText(newDirectory, dontSendNotification);
}

String FileAndDirectoryControls::getCurrentDirectoryDisplayed() const
{
    return currentDirectoryDataLabel.getText();
}

void FileAndDirectoryControls::buttonClicked(Button* button)
{
    if(button == &changeDirectoryButton)
    {
        FileChooser chooser("Select New Directory");
    
        if(chooser.browseForDirectory())
        {
            File newDirectory = chooser.getResult();
        
            currentDirectoryDataLabel.setText(newDirectory.getFullPathName(), dontSendNotification);
        }
    }
    
    else if(button == &moveButton)
    {
        if(currentDirectoryDataLabel.getText().isNotEmpty())
        {
            sendActionMessage("File and Dir Apply Button Clicked");
        }
    }
    
    else if(button == &closeButton)
    {
        sendActionMessage("Extra Info Close Button Clicked");
    }
}

String FileAndDirectoryControls::getWildcardPath() const
{
    return folderHierachyLabel.getText();
}

String FileAndDirectoryControls::getNewDirAndWildcardPath() const
{
    if(currentDirectoryDataLabel.getText().isNotEmpty())
    {
        return currentDirectoryDataLabel.getText() + "/" + folderHierachyEditor.getText();
    }
    return currentDirectoryDataLabel.getText();
}
