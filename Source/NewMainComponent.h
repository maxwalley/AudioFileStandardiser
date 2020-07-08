/*
  ==============================================================================

    NewMainComponent.h
    Created: 24 Jun 2020 8:15:51pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "IntroComponent.h"
#include "Mediator.h"
#include "BatchRenameControls.h"
#include "FileAndDirectoryControls.h"
#include "AudioPlayerGUI.h"

//==============================================================================
/*
*/
class NewMainComponent    : public Component
{
public:
    enum componentsToDisplay
    {
        Intro = 0,
        Table = 1,
        RenameControls = 2,
        FileAndFolderControls = 4
    };
    
    NewMainComponent();
    ~NewMainComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void setComponentsToDisplay(int components);
    
    void updateTable();
    
    int showTablePopup();
    
    void setAdditionalAudioSource(AudioSource* newAudioSource);

private:
    
    componentsToDisplay currentComponents;
    
    IntroComponent introComponent;
    TableListBox table;
    BatchRenameControls* renameControls;
    FileAndDirectoryControls* fileControls;
    AudioPlayerGUI* audioPlayerControls;
    
    AudioSource* additionalAudioSource;
    
    Viewport extraInfoViewport;
    
    PopupMenu tablePopup;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewMainComponent)
};
