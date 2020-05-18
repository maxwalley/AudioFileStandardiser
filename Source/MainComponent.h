/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioFileTable.h"
//==============================================================================

class MainComponent   : public Component,
                        public Button::Listener
{
public:
    MainComponent();
    ~MainComponent();
   
    void paint (Graphics&) override;
    void resized() override;

private:
    void buttonClicked(Button* button) override;
    
    TextButton openSourceButton;
    
    Array<File> currentFiles;
    StringChecker stringChecker;
    
    FileChooser chooser;
    
    bool fileLoaded;
    
    AudioFileTable fileTable;
    
    AudioFormatManager manager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
