/*
  ==============================================================================

    FileAndDirectoryControls.cpp
    Created: 4 Jun 2020 5:06:31pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileAndDirectoryControls.h"
#include "Mediator.h"

//==============================================================================
FileAndDirectoryControls::FileAndDirectoryControls()    :   changeDirectoryButton("Select New Directory"), moveButton("Move Files"), closeButton("Close")
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
    moveButton.addListener(Mediator::getInstance());
    moveButton.setComponentID("file_controls_move");
    
    addAndMakeVisible(closeButton);
    closeButton.addListener(Mediator::getInstance());
    closeButton.setComponentID("extra_info_close");
}

FileAndDirectoryControls::~FileAndDirectoryControls()
{
}

void FileAndDirectoryControls::paint (Graphics& g)
{
    g.setColour(Colours::white);
    g.setFont(Font(20));
    g.drawText("File and Directory", 0, 5, getWidth(), 30, Justification::centred);
}

void FileAndDirectoryControls::resized()
{
    currentDirectoryLabel.setBounds(0, 40, getWidth(), 20);
    currentDirectoryDataLabel.setBounds(5, 65, getWidth()-10, 50);
    
    changeDirectoryButton.setBounds(5, 120, getWidth()-10, 30);
    
    folderHierachyLabel.setBounds(0, 170, getWidth(), 20);
    folderHierachyEditor.setBounds(5, 195, getWidth()-10, 30);
    
    moveButton.setBounds(5, 245, getWidth()-10, 30);
    
    closeButton.setBounds(5, 285, getWidth()-10, 30);
}


void FileAndDirectoryControls::setCurrentDirectory(const String& newDirectory)
{
    currentDirectoryDataLabel.setText(newDirectory, dontSendNotification);
}

std::optional<String> FileAndDirectoryControls::getCurrentDirectoryDisplayed() const
{
    if(currentDirectoryDataLabel.getText().isEmpty())
    {
        return std::nullopt;
    }
    return currentDirectoryDataLabel.getText();
}

std::optional<String> FileAndDirectoryControls::getWildcardPath() const
{
    if(folderHierachyEditor.isEmpty())
    {
        return std::nullopt;
    }
    return folderHierachyEditor.getText();
}

std::optional<String> FileAndDirectoryControls::getNewDirAndWildcardPath() const
{
    if(!getCurrentDirectoryDisplayed())
    {
        return std::nullopt;
    }
    return *getCurrentDirectoryDisplayed() + "/" + getWildcardPath().value_or("");
}

void FileAndDirectoryControls::buttonClicked(Button* button)
{
    //Puts the new directory path in the current directory editor
    if(button == &changeDirectoryButton)
    {
        FileChooser chooser("Select New Directory");
    
        if(chooser.browseForDirectory())
        {
            File newDirectory = chooser.getResult();
        
            currentDirectoryDataLabel.setText(newDirectory.getFullPathName(), dontSendNotification);
        }
    }
}
