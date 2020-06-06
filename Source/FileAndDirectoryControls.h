/*
  ==============================================================================

    FileAndDirectoryControls.h
    Created: 4 Jun 2020 5:06:31pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class FileAndDirectoryControls    : public Component,
                                    public Button::Listener
{
public:
    FileAndDirectoryControls();
    ~FileAndDirectoryControls();

    void paint (Graphics&) override;
    void resized() override;
    
    void setDataSet(bool isDataSet);
    
    void setCurrentDirectory(String newDirectory);
    String getCurrentDirectoryDisplayed() const;

private:
    
    void buttonClicked(Button* button) override;
    
    bool dataSet;
    
    Label currentDirectoryLabel;
    TextEditor currentDirectoryEditor;
    
    TextButton changeDirectoryButton;
    
    TextEditor folderHierachyEditor;
    Label folderHierachyLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileAndDirectoryControls)
};
