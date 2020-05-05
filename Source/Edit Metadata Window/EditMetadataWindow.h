/*
  ==============================================================================

    EditMetadataWindow.h
    Created: 5 May 2020 1:14:05pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "ComponentWindow.h"

//==============================================================================
/*
*/
class EditMetadataWindow    : public ComponentWindow
{
public:
    EditMetadataWindow();
    ~EditMetadataWindow();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditMetadataWindow)
};
