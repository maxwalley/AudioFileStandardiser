/*
  ==============================================================================

    introComponent.h
    Created: 24 Jun 2020 12:25:06pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class IntroComponent    :   public Component
{
public:
    IntroComponent();
    ~IntroComponent();

    void resized() override;

private:
    
    TextButton openSourceButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IntroComponent)
};
