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
                                    public Button::Listener,
                                    public ActionBroadcaster
{
public:
    FileAndDirectoryControls();
    ~FileAndDirectoryControls();

    void paint (Graphics&) override;
    void resized() override;
    
    void setCurrentDirectory(const String& newDirectory);
    std::optional<String> getCurrentDirectoryDisplayed() const;
    
    std::optional<String> getWildcardPath() const;

    //Returns the current directory with the wildcard path appended to the end
    //Returns std::nullopt if current directory is empty
    std::optional<String> getNewDirAndWildcardPath() const;
private:
    
    void buttonClicked(Button* button) override;
    
    Label currentDirectoryLabel;
    Label currentDirectoryDataLabel;
    
    TextButton changeDirectoryButton;
    
    TextEditor folderHierachyEditor;
    Label folderHierachyLabel;
    
    TextButton moveButton;
    
    TextButton closeButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileAndDirectoryControls)
};
