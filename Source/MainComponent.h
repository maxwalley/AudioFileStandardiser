/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioFileTable.h"
#include "AudioMetadataManager.h"
#include "StringChecker.h"
#include "DataHandler.h"
#include "Mediator.h"
#include "Logger.h"
//==============================================================================


class MainComponent   : public Component,
                        public Button::Listener,
                        public MenuBarModel,
                        public ActionListener
{
public:
    MainComponent();
    ~MainComponent();
   
    void paint (Graphics&) override;
    void resized() override;
    
private:
    void buttonClicked(Button* button) override;
    
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
    
    void actionListenerCallback(const String& message) override;
    
    bool batchControlsShown;
    
    TextButton openSourceButton;
    
    bool fileLoaded;
    
    AudioFileTable fileTable;
    
    bool fileNamesToChangeWithTitle;
    
    bool fileAndFolderControlsShown;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
