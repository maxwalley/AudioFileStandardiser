/*
  ==============================================================================

    AudioPlayerGUI.cpp
    Created: 7 Jul 2020 3:37:27pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayerGUI.h"

#include "Mediator.h"

//==============================================================================
AudioPlayerGUI::AudioPlayerGUI()
{
    playPauseButton = std::make_unique<PlayerGUIButton>(PlayerGUIButton::ControlType::play);
    addAndMakeVisible(playPauseButton.get());
    playPauseButton->setComponentID("player_play_button");
    playPauseButton->addListener(Mediator::getInstance());
}

AudioPlayerGUI::~AudioPlayerGUI()
{
}

void AudioPlayerGUI::paint (Graphics& g)
{
    g.fillAll(Colours::dimgrey);
}

void AudioPlayerGUI::resized()
{
    playPauseButton->setBounds(getWidth()/2 - 20, getHeight()/2 - 20, 40, 40);
}

void AudioPlayerGUI::changePlayButtonState(bool state)
{
    //if(state < 2 && state >= 0)
    //{
        playPauseButton->changeFunction(PlayerGUIButton::ControlType(state));
    //}
}

bool AudioPlayerGUI::getPlayButtonState()
{
    return bool(playPauseButton->getFunction());
}
