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
NewMainComponent::NewMainComponent()    :   currentComponents(intro)
{
    setSize(introComponent.getWidth(), introComponent.getHeight());
    addAndMakeVisible(introComponent);
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
    if(currentComponents == 0)
    {
        introComponent.setBounds(0, 0, getWidth(), getHeight());
    }
}

void NewMainComponent::setComponentToDisplay(componentsToDisplay component)
{
    currentComponents = component;
}
