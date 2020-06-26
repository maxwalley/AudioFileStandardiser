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
    enum componentsToDisplay
    {
        intro = 0,
        table = 1
    };
    
    NewMainComponent();
    ~NewMainComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void setComponentToDisplay(componentsToDisplay component);

private:
    
    componentsToDisplay currentComponents;
    
    IntroComponent introComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewMainComponent)
};
