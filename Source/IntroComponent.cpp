/*
  ==============================================================================

    introComponent.cpp
    Created: 24 Jun 2020 12:25:06pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "IntroComponent.h"
#include "AudioFileStandardiserApplication.h"

//==============================================================================
IntroComponent::IntroComponent()    :   openSourceButton("Open Source")
{
    addAndMakeVisible(openSourceButton);
    
    openSourceButton.addListener(AudioFileStandardiserApplication::getMediator());
    
    openSourceButton.setComponentID("intro_openSourceButton");
    
    setSize(300, 200);
}

IntroComponent::~IntroComponent()
{
}

void IntroComponent::resized()
{
    openSourceButton.setBounds(getWidth()/2-50, getHeight()/2-15, 100, 30);
}
