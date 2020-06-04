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
    
}

void FileAndDirectoryControls::setDataSet(bool isDataSet)
{
    dataSet = isDataSet;
}

void FileAndDirectoryControls::setCurrentDirectory(String newDirectory)
{
    
}

String FileAndDirectoryControls::getCurrentDirectory() const
{
    
}
