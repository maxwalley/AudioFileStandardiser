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
    
    
    addAndMakeVisible(addCharsToStartEditor);
    addAndMakeVisible(addCharsToStartLabel);
    addCharsToStartLabel.setText("Chars to Start", dontSendNotification);
    
    addAndMakeVisible(addCharsToPositionEditor);
    addAndMakeVisible(addCharsToPositionLabel);
    addCharsToPositionLabel.setText("Characters", dontSendNotification);
    
    addAndMakeVisible(positionToAddToEditor);
    positionToAddToEditor.setInputRestrictions(0, "0123456789");
    addAndMakeVisible(positionToAddToLabel);
    positionToAddToLabel.setText("At Position", dontSendNotification);
    
    addAndMakeVisible(addCharsToEndEditor);
    addAndMakeVisible(addCharsToEndLabel);
    addCharsToEndLabel.setText("Chars to End", dontSendNotification);
    
    
    addAndMakeVisible(replaceCharEditor);
    addAndMakeVisible(replaceCharLabel);
    replaceCharLabel.setText("Replace", dontSendNotification);
    
    addAndMakeVisible(replaceCharWithEditor);
    addAndMakeVisible(replaceCharWithLabel);
    replaceCharWithLabel.setText("With", dontSendNotification);
    
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
        
        g.drawText("Replace", 20, 400, 70, 20, Justification::centred);
        
        Path path;
        path.startNewSubPath(80, 70);
        path.lineTo(184, 70);
        path.lineTo(184, 190);
        path.lineTo(6, 190);
        path.lineTo(6, 70);
        path.lineTo(20, 70);
        
        path.startNewSubPath(50, 230);
        path.lineTo(184, 230);
        path.lineTo(184, 373);
        path.lineTo(6, 373);
        path.lineTo(6, 230);
        path.lineTo(20, 230);
        
        path.startNewSubPath(90, 410);
        path.lineTo(184, 410);
        path.lineTo(184, 500);
        path.lineTo(6, 500);
        path.lineTo(6, 410);
        path.lineTo(20, 410);
        
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
        
        
        addCharsToStartEditor.setBounds(10, 250, 70, 20);
        addCharsToStartLabel.setBounds(85, 250, 100, 20);
        
        addCharsToPositionEditor.setBounds(10, 280, 70, 20);
        addCharsToPositionLabel.setBounds(85, 280, 100, 20);
        
        positionToAddToEditor.setBounds(10, 303, 30, 20);
        positionToAddToLabel.setBounds(45, 303, 100, 20);
        
        addCharsToEndEditor.setBounds(10, 333, 70, 20);
        addCharsToEndLabel.setBounds(85, 333, 100, 20);
        
        replaceCharEditor.setBounds(10, 430, 70, 20);
        replaceCharLabel.setBounds(85, 430, 100, 20);
        
        replaceCharWithEditor.setBounds(10, 460, 70, 20);
        replaceCharWithLabel.setBounds(85, 460, 100, 20);
        
        applyButton.setBounds(6, 520, 178, 30);
        
        closeButton.setBounds(6, 560, 178, 30);
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

String BatchRenameControls::getCharsToAddToStart()
{
    return addCharsToStartEditor.getText();
}

String BatchRenameControls::getCharsToAddToPosition()
{
    return addCharsToPositionEditor.getText();
}

int BatchRenameControls::getPositionToAdd()
{
    return positionToAddToEditor.getText().getIntValue();
}

String BatchRenameControls::getCharsToAddToEnd()
{
    return addCharsToEndEditor.getText();
}

String BatchRenameControls::getCharToReplace()
{
    return replaceCharEditor.getText();
}

String BatchRenameControls::getCharToReplaceWith()
{
    return replaceCharWithEditor.getText();
}
