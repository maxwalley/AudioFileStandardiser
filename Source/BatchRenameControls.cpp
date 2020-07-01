/*
  ==============================================================================

    BatchRenameControls.cpp
    Created: 26 May 2020 1:28:26pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "BatchRenameControls.h"
#include "Mediator.h"

//==============================================================================
BatchRenameControls::BatchRenameControls() : applyButton("Apply"), resetButton("Reset"), closeButton("Close")
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
    
    
    addAndMakeVisible(defaultCapSettingsToggle);
    addAndMakeVisible(defaultCapSettingsLabel);
    defaultCapSettingsLabel.setText("Default Settings", dontSendNotification);
    
    addAndMakeVisible(capAllWordsToggle);
    capAllWordsToggle.addListener(this);
    addAndMakeVisible(capAllWordsLabel);
    capAllWordsLabel.setText("Everything", dontSendNotification);
    
    addAndMakeVisible(decapAllWordsToggle);
    decapAllWordsToggle.addListener(this);
    addAndMakeVisible(decapAllWordsLabel);
    decapAllWordsLabel.setText("Decapatalise Everything", dontSendNotification);
    
    addAndMakeVisible(capWordEditor);
    capWordEditor.addMouseListener(this, false);
    addAndMakeVisible(capWordLabel);
    capWordLabel.setText("Word", dontSendNotification);
    
    addAndMakeVisible(capStartOfAllWordsToggle);
    capStartOfAllWordsToggle.addListener(this);
    addAndMakeVisible(capStartOfAllWordsLabel);
    capStartOfAllWordsLabel.setText("Start of All Words", dontSendNotification);
    
    addAndMakeVisible(capStartOfWordEditor);
    capStartOfWordEditor.addMouseListener(this, false);
    addAndMakeVisible(capStartOfWordLabel);
    capStartOfWordLabel.setText("Start of Word", dontSendNotification);
    
    
    addAndMakeVisible(applyButton);
    applyButton.addListener(Mediator::getInstance());
    applyButton.setComponentID("batch_apply");
    
    addAndMakeVisible(resetButton);
    resetButton.addListener(this);
    
    addAndMakeVisible(closeButton);
    closeButton.addListener(Mediator::getInstance());
}

BatchRenameControls::~BatchRenameControls()
{
    
}

void BatchRenameControls::paint (Graphics& g)
{
        g.setColour(Colours::white);
        g.setFont(Font(20));
        g.drawText("Batch Rename", 0, 5, getWidth(), 30, Justification::centred);
    
        g.setFont(Font(14));
        g.drawText("Remove", 25, 60, 60, 20, Justification::left);
        
        g.drawText("Add", 25, 220, 30, 20, Justification::left);
        
        g.drawText("Replace", 25, 400, 70, 20, Justification::left);
        
        g.drawText("Capatalise", 25, 530, 100, 20, Justification::left);
        
        Path path;
        path.startNewSubPath(75, 70);
        path.lineTo(184, 70);
        path.lineTo(184, 190);
        path.lineTo(6, 190);
        path.lineTo(6, 70);
        path.lineTo(20, 70);
        
        path.startNewSubPath(53, 230);
        path.lineTo(184, 230);
        path.lineTo(184, 373);
        path.lineTo(6, 373);
        path.lineTo(6, 230);
        path.lineTo(20, 230);
        
        path.startNewSubPath(75, 410);
        path.lineTo(184, 410);
        path.lineTo(184, 500);
        path.lineTo(6, 500);
        path.lineTo(6, 410);
        path.lineTo(20, 410);
        
        path.startNewSubPath(90, 540);
        path.lineTo(184, 540);
        path.lineTo(184, 750);
        path.lineTo(6, 750);
        path.lineTo(6, 540);
        path.lineTo(20, 540);
        
        g.strokePath(path, PathStrokeType(1.0f));
}

void BatchRenameControls::resized()
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
        
        
        defaultCapSettingsToggle.setBounds(10, 560, 25, 20);
        defaultCapSettingsToggle.addListener(this);
        defaultCapSettingsLabel.setBounds(30, 560, 160, 20);
        
        capAllWordsToggle.setBounds(10, 590, 25, 20);
        capAllWordsLabel.setBounds(30, 590, 160, 20);
        
        decapAllWordsToggle.setBounds(10, 620, 25, 20);
        decapAllWordsLabel.setBounds(30, 620, 160, 20);
        
        capWordEditor.setBounds(10, 650, 70, 20);
        capWordLabel.setBounds(85, 650, 100, 20);
        
        capStartOfAllWordsToggle.setBounds(10, 680, 25, 20);
        capStartOfAllWordsLabel.setBounds(30, 680, 160, 20);
        
        capStartOfWordEditor.setBounds(10, 710, 70, 20);
        capStartOfWordLabel.setBounds(85, 710, 100, 20);
    
        
        applyButton.setBounds(6, 770, 178, 30);
        
        resetButton.setBounds(6, 810, 178, 30);
        
        closeButton.setBounds(6, 850, 178, 30);
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

std::optional<String> BatchRenameControls::getCharsToRemove()
{
    if(!removeCharsEditor.isEmpty())
    {
        return removeCharsEditor.getText();
    }
    return std::nullopt;
}

void BatchRenameControls::buttonClicked(Button* button)
{
    if(button == &resetButton)
    {
        titleToggle.setToggleState(false, dontSendNotification);
        artistToggle.setToggleState(false, dontSendNotification);
        albumToggle.setToggleState(false, dontSendNotification);
        
        removeCharsEditor.clear();
        removeStartCharsEditor.clear();
        removeEndCharsEditor.clear();
        
        addCharsToStartEditor.clear();
        addCharsToEndEditor.clear();
        addCharsToPositionEditor.clear();
        positionToAddToEditor.clear();
        
        replaceCharEditor.clear();
        replaceCharWithEditor.clear();
        
        defaultCapSettingsToggle.setToggleState(false, dontSendNotification);
        capAllWordsToggle.setToggleState(false, dontSendNotification);
        decapAllWordsToggle.setToggleState(false, dontSendNotification);
        capWordEditor.clear();
        capStartOfAllWordsToggle.setToggleState(false, dontSendNotification);
        capStartOfWordEditor.clear();
        
        repaint();
    }
    
    else if(button == &closeButton)
    {
        sendActionMessage("Extra Info Close Button Clicked");
    }
    
    else if(button == &defaultCapSettingsToggle)
    {
        capAllWordsToggle.setToggleState(false, dontSendNotification);
        decapAllWordsToggle.setToggleState(false, dontSendNotification);
        capWordEditor.clear();
        capStartOfAllWordsToggle.setToggleState(false, dontSendNotification);
        capStartOfWordEditor.clear();
        repaint();
    }
    
    else if(button == &capAllWordsToggle)
    {
        if(defaultCapSettingsToggle.getToggleState())
        {
            defaultCapSettingsToggle.setToggleState(false, dontSendNotification);
        }
        
        else if(capAllWordsToggle.getToggleState())
        {
            decapAllWordsToggle.setToggleState(false, dontSendNotification);
        }
    }
    
    else if(button == &decapAllWordsToggle)
    {
        if(defaultCapSettingsToggle.getToggleState())
        {
            defaultCapSettingsToggle.setToggleState(false, dontSendNotification);
        }
        
        else if(decapAllWordsToggle.getToggleState())
        {
            capAllWordsToggle.setToggleState(false, dontSendNotification);
        }
    }
    
    else if(button == &capStartOfAllWordsToggle)
    {
        if(defaultCapSettingsToggle.getToggleState())
        {
            defaultCapSettingsToggle.setToggleState(false, dontSendNotification);
        }
    }
}

void BatchRenameControls::mouseDown(const MouseEvent& event)
{
    if(event.originalComponent == &capWordEditor || event.originalComponent ==&capStartOfWordEditor)
    {
        if(defaultCapSettingsToggle.getToggleState())
        {
            defaultCapSettingsToggle.setToggleState(false, dontSendNotification);
        }
    }
}

std::optional<int> BatchRenameControls::getNumStartCharsToRemove()
{
    if(!removeStartCharsEditor.isEmpty())
    {
        return removeStartCharsEditor.getText().getIntValue();
    }
    return std::nullopt;
}

std::optional<int> BatchRenameControls::getNumEndCharsToRemove()
{
    if(!removeEndCharsEditor.isEmpty())
    {
        return removeEndCharsEditor.getText().getIntValue();
    }
    return std::nullopt;
}

std::optional<String> BatchRenameControls::getCharsToAddToStart()
{
    if(!addCharsToStartEditor.isEmpty())
    {
        return addCharsToStartEditor.getText();
    }
    return std::nullopt;
}

std::optional<String> BatchRenameControls::getCharsToAddToPosition()
{
    if(!addCharsToPositionEditor.isEmpty())
    {
        return addCharsToPositionEditor.getText();
    }
    return std::nullopt;
}

std::optional<int> BatchRenameControls::getPositionToAdd()
{
    if(!positionToAddToEditor.isEmpty())
    {
        return positionToAddToEditor.getText().getIntValue();
    }
    return std::nullopt;
}

std::optional<String> BatchRenameControls::getCharsToAddToEnd()
{
    if(!addCharsToEndEditor.isEmpty())
    {
        return addCharsToEndEditor.getText();
    }
    return std::nullopt;
}

std::optional<String> BatchRenameControls::getCharToReplace()
{
    if(!replaceCharEditor.isEmpty())
    {
        return replaceCharEditor.getText();
    }
    return std::nullopt;
}

std::optional<String> BatchRenameControls::getCharToReplaceWith()
{
    if(!replaceCharWithEditor.isEmpty())
    {
        return replaceCharWithEditor.getText();
    }
    return std::nullopt;
}

bool BatchRenameControls::getDefaultCapSettings() const
{
    return defaultCapSettingsToggle.getToggleState();
}

bool BatchRenameControls::getCapAllWords() const
{
    return capAllWordsToggle.getToggleState();
}

bool BatchRenameControls::getDecapAllWords() const
{
    return decapAllWordsToggle.getToggleState();
}

std::optional<String> BatchRenameControls::getCapWord() const
{
    if(!capWordEditor.isEmpty())
    {
        return capWordEditor.getText();
    }
    return std::nullopt;
}

bool BatchRenameControls::getCapStartOfAllWords() const
{
    return capStartOfAllWordsToggle.getToggleState();
}

std::optional<String> BatchRenameControls::getCapStartOfWord() const
{
    if(!capStartOfWordEditor.isEmpty())
    {
        return capStartOfWordEditor.getText();
    }
    return std::nullopt;
}
