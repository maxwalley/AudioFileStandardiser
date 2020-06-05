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
class FileAndDirectoryControls    : public Component
{
public:
    FileAndDirectoryControls();
    ~FileAndDirectoryControls();

    void paint (Graphics&) override;
    void resized() override;
    
    void setDataSet(bool isDataSet);
    
    void setCurrentDirectory(String newDirectory);
    String getCurrentDirectory() const;

private:
    
    bool dataSet;
    
    Label currentDirectoryDataLabel;
    Label currentDirectoryLabel;
    
    TextButton changeDirectoryButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileAndDirectoryControls)
};
