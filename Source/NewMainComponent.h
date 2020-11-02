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
#include "BatchRenameControls.h"
#include "FileAndDirectoryControls.h"

//==============================================================================
/*
*/

class NewMainComponent    : public Component,
                            public FileDragAndDropTarget
{
public:
    enum componentsToDisplay
    {
        Intro = 0,
        Table = 1,
        RenameControls = 2,
        FileAndFolderControls = 4
    };
    
    struct SizeLimits
    {
        int maxWidth;
        int maxHeight;
        int minWidth;
        int minHeight;
        int defWidth;
        int defHeight;
    };
    
    NewMainComponent();
    ~NewMainComponent();

    void paintOverChildren (Graphics&) override;
    void resized() override;
    
    void setComponentsToDisplay(int components);
    int getDisplayedComponents() const;
    
    void updateTable();
    
    int showTablePopup();
    
    void setAdditionalAudioSource(AudioSource* newAudioSource);
    
    SizeLimits getCurrentSizeLimits() const;
    
    class Listener
    {
    public:
        Listener();
        virtual ~Listener();
        
        virtual void filesDropped(const StringArray& files){};
    };
    
    void addListener(Listener* newListener);
    void removeListener(Listener* lisToRemove);

private:
    
    bool isInterestedInFileDrag(const StringArray& files) override;
    void fileDragEnter(const StringArray& files, int x, int y) override;
    void fileDragExit(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
    
    componentsToDisplay currentComponents;
    
    IntroComponent introComponent;
    TableListBox table;
    BatchRenameControls* renameControls;
    FileAndDirectoryControls* fileControls;
    
    AudioSource* additionalAudioSource;
    
    Viewport extraInfoViewport;
    
    PopupMenu tablePopup;
    
    SizeLimits currentLimits;
    
    std::vector<Listener*> listeners;
    
    bool fileDrag = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewMainComponent)
};
