/*
  ==============================================================================

    BatchRenameControls.h
    Created: 26 May 2020 1:28:26pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "tag_c.h"
#include "StringChecker.h"

//==============================================================================
/*
*/

class BatchRenameControls    : public Component,
                               public Button::Listener,
                               public ActionBroadcaster
{
public:
    
    enum ButtonsActive
    {
        titleButton = 1,
        artistButton = 2,
        albumButton = 4
    };
    
    BatchRenameControls();
    ~BatchRenameControls();

    void paint (Graphics&) override;
    void resized() override;
    
    void setDataSet(bool hasDataBeenSet);
    
    ButtonsActive getButtonsActive();
    
    String getCharsToRemove();
    
    int getNumStartCharsToRemove();
    
    int getNumEndCharsToRemove();
    
    String getCharsToAddToStart();
    
    String getCharsToAddToPosition();
    
    int getPositionToAdd();
    
    String getCharsToAddToEnd();
    
    String getCharToReplace();
    
    String getCharToReplaceWith();
    
    bool getDefaultCapSettings() const;
    
    bool getCapAllWords() const;
    
    bool getDecapAllWords() const;
    
    String getCapWord() const;
    
    bool getCapStartOfAllWords() const;
    
    String getCapStartOfWord() const;

private:
    
    void buttonClicked(Button* button) override;
    
    void mouseDown(const MouseEvent& event) override;

    
    bool dataSet;
    
    ToggleButton titleToggle;
    ToggleButton artistToggle;
    ToggleButton albumToggle;
    
    Label titleToggleLabel;
    Label artistToggleLabel;
    Label albumToggleLabel;
    
    TextEditor removeCharsEditor;
    Label removeCharsDescripLabel;
    
    TextEditor removeStartCharsEditor;
    Label removeStartCharsLabel;
    
    TextEditor removeEndCharsEditor;
    Label removeEndCharsLabel;
    
    
    TextEditor addCharsToStartEditor;
    Label addCharsToStartLabel;
    
    TextEditor addCharsToPositionEditor;
    Label addCharsToPositionLabel;
    
    TextEditor positionToAddToEditor;
    Label positionToAddToLabel;
    
    TextEditor addCharsToEndEditor;
    Label addCharsToEndLabel;
    
    
    TextEditor replaceCharEditor;
    Label replaceCharLabel;
    
    TextEditor replaceCharWithEditor;
    Label replaceCharWithLabel;
    
    
    ToggleButton defaultCapSettingsToggle;
    Label defaultCapSettingsLabel;
    
    ToggleButton capAllWordsToggle;
    Label capAllWordsLabel;
    
    ToggleButton decapAllWordsToggle;
    Label decapAllWordsLabel;
    
    TextEditor capWordEditor;
    Label capWordLabel;
    
    ToggleButton capStartOfAllWordsToggle;
    Label capStartOfAllWordsLabel;
    
    TextEditor capStartOfWordEditor;
    Label capStartOfWordLabel;
    
    
    TextButton applyButton;
    
    TextButton resetButton;
    
    TextButton closeButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BatchRenameControls)
};
