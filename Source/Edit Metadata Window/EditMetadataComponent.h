/*
  ==============================================================================

    EditMetadataComponent.h
    Created: 5 May 2020 1:14:49pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class EditMetadataComponent    : public Component
{
public:
    EditMetadataComponent();
    ~EditMetadataComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditMetadataComponent)
};
