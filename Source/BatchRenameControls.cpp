/*
  ==============================================================================

    BatchRenameControls.cpp
    Created: 26 May 2020 1:28:26pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "BatchRenameControls.h"

//==============================================================================
BatchRenameControls::BatchRenameControls() : dataSet(false), applyButton("Apply"), closeButton("Close")
{
    addAndMakeVisible(titleToggle);
    addAndMakeVisible(artistToggle);
    addAndMakeVisible(albumToggle);
    
    addAndMakeVisible(titleToggleLabel);
    titleToggleLabel.setText("Title", dontSendNotification);
    addAndMakeVisible(artistToggleLabel);
    artistToggleLabel.setText("Artist", dontSendNotification);
    addAndMakeVisible(albumToggleLabel);
    albumToggleLabel.setText("Album", dontSendNotification);
    
    addAndMakeVisible(removeCharsEditor);
    addAndMakeVisible(removeCharsDescripLabel);
    removeCharsDescripLabel.setText("Characters", dontSendNotification);
    
    addAndMakeVisible(removeStartCharsEditor);
    removeStartCharsEditor.setInputRestrictions(0, "0123456789");
    addAndMakeVisible(removeStartCharsLabel);
    removeStartCharsLabel.setText("Num Start Chars", dontSendNotification);
    
    addAndMakeVisible(removeEndCharsEditor);
    removeEndCharsEditor.setInputRestrictions(0, "0123456789");
    addAndMakeVisible(removeEndCharsLabel);
    removeEndCharsLabel.setText("Num End Chars", dontSendNotification);
    
    addAndMakeVisible(applyButton);
    applyButton.addListener(this);
    
    addAndMakeVisible(closeButton);
    closeButton.addListener(this);
}

BatchRenameControls::~BatchRenameControls()
{
    
}

void BatchRenameControls::paint (Graphics& g)
{
    if(dataSet == true)
    {
        g.setColour(Colours::white);
        g.setFont(Font(20));
        g.drawText("Batch Rename", 0, 5, getWidth(), 30, Justification::centred);
    
        g.setFont(Font(14));
        g.drawText("Remove", 20, 60, 60, 20, Justification::centred);
        
        g.drawText("Add", 20, 220, 30, 20, Justification::centred);
        
        Path path;
        path.startNewSubPath(80, 70);
        path.lineTo(184, 70);
        path.lineTo(184, 190);
        path.lineTo(6, 190);
        path.lineTo(6, 70);
        path.lineTo(20, 70);
        
        path.startNewSubPath(50, 230);
        path.lineTo(184, 230);
        path.lineTo(184, 270);
        path.lineTo(6, 270);
        path.lineTo(6, 230);
        path.lineTo(20, 230);
        
        g.strokePath(path, PathStrokeType(1.0f));
    }
}

void BatchRenameControls::resized()
{
    if(dataSet == true)
    {
        //Made to be same size as table toggle buttons
        titleToggle.setBounds(3, 35, 25, 22);
        artistToggle.setBounds(66, 35, 25, 22);
        albumToggle.setBounds(133, 35, 25, 22);
        
        titleToggleLabel.setBounds(21, 35, 40, 22);
        artistToggleLabel.setBounds(84, 35, 40, 22);
        albumToggleLabel.setBounds(151, 35, 40, 22);
        
        removeCharsEditor.setBounds(10, 90, 70, 20);
        removeCharsDescripLabel.setBounds(85, 90, 100, 20);
        
        removeStartCharsEditor.setBounds(10, 120, 50, 20);
        removeStartCharsLabel.setBounds(65, 120, 100, 20);
        
        removeEndCharsEditor.setBounds(10, 150, 50, 20);
        removeEndCharsLabel.setBounds(65, 150, 100, 20);
        
        applyButton.setBounds(6, 280, 178, 30);
        
        closeButton.setBounds(6, 320, 178, 30);
    }
}

void BatchRenameControls::setDataSet(bool hasDataBeenSet)
{
    dataSet = hasDataBeenSet;
}

BatchRenameControls::ButtonsActive BatchRenameControls::getButtonsActive()
{
    ButtonsActive activeButtons = ButtonsActive(0);
    
    if(titleToggle.getToggleState() == true)
    {
        activeButtons = ButtonsActive(activeButtons + titleButton);
    }
    
    if(artistToggle.getToggleState() == true)
    {
        activeButtons = ButtonsActive(activeButtons + artistButton);
    }
    
    if(albumToggle.getToggleState() == true)
    {
        activeButtons = ButtonsActive(activeButtons + albumButton);
    }
    
    return activeButtons;
}

String BatchRenameControls::getCharsToRemove()
{
    return removeCharsEditor.getText();
}

void BatchRenameControls::buttonClicked(Button* button)
{
    if(button == &applyButton)
    {
        sendActionMessage("Apply Button Clicked");
    }
    
    else if(button == &closeButton)
    {
        sendActionMessage("Close Button Clicked");
    }
}

int BatchRenameControls::getNumStartCharsToRemove()
{
    return removeStartCharsEditor.getText().getIntValue();
}

int BatchRenameControls::getNumEndCharsToRemove()
{
    return removeEndCharsEditor.getText().getIntValue();
}
