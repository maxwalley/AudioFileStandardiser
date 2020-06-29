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
        Intro = 0,
        Table = 1
    };
    
    NewMainComponent();
    ~NewMainComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void setComponentToDisplay(componentsToDisplay component);
    
    void updateTable();

private:
    
    componentsToDisplay currentComponents;
    
    IntroComponent introComponent;
    TableListBox table;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewMainComponent)
};
