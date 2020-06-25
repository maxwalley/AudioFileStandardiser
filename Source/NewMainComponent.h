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

//==============================================================================
/*
*/
class NewMainComponent    : public Component
{
public:
    NewMainComponent();
    ~NewMainComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    IntroComponent introComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewMainComponent)
};
