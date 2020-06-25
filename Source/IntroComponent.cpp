/*
  ==============================================================================

    introComponent.cpp
    Created: 24 Jun 2020 12:25:06pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "IntroComponent.h"

//==============================================================================
IntroComponent::IntroComponent()    :   openSourceButton("Open Source")
{
    addAndMakeVisible(openSourceButton);
    
    openSourceButton.addListener(Mediator::getInstance());
    
    openSourceButton.setComponentID("intro_openSourceButton");
    
    setSize(300, 200);
}

IntroComponent::~IntroComponent()
{
}

void IntroComponent::resized()
{
    openSourceButton.setBounds(100, 60, 100, 30);
}
