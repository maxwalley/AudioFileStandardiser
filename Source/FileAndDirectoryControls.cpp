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
FileAndDirectoryControls::FileAndDirectoryControls()    :   dataSet(false), changeDirectoryButton("Change")
{
    addAndMakeVisible(currentDirectoryLabel);
    currentDirectoryLabel.setText("Selected Files Directory", dontSendNotification);
    addAndMakeVisible(currentDirectoryDataLabel);
    currentDirectoryDataLabel.setEditable(false);
    currentDirectoryDataLabel.setColour(Label::outlineColourId, Colour(141, 152, 155));
    currentDirectoryDataLabel.setColour(Label::backgroundColourId, Colour(37, 50, 55));
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
    }
}

void FileAndDirectoryControls::setDataSet(bool isDataSet)
{
    dataSet = isDataSet;
}

void FileAndDirectoryControls::setCurrentDirectory(String newDirectory)
{
    currentDirectoryDataLabel.setText(newDirectory, dontSendNotification);
}

String FileAndDirectoryControls::getCurrentDirectory() const
{
    
}
