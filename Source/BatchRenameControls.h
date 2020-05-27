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

private:
    
    void buttonClicked(Button* button) override;
    
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
    
    TextButton applyButton;
    
    TextButton closeButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BatchRenameControls)
};
