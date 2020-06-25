/*
  ==============================================================================

    NewMainComponent.cpp
    Created: 24 Jun 2020 8:15:51pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NewMainComponent.h"

//==============================================================================
NewMainComponent::NewMainComponent()
{
    addAndMakeVisible(introComponent);
    setSize(introComponent.getWidth(), introComponent.getHeight());
}

NewMainComponent::~NewMainComponent()
{
    Mediator::closeInstance();
}

void NewMainComponent::paint (Graphics& g)
{
    
}

void NewMainComponent::resized()
{
    introComponent.setBounds(0, 0, getWidth(), getHeight());
}
