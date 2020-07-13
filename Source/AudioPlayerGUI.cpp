/*
  ==============================================================================

    AudioPlayerGUI.cpp
    Created: 7 Jul 2020 3:37:27pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayerGUI.h"
#include "AudioFileStandardiserApplication.h"

//==============================================================================
AudioPlayerGUI::AudioPlayerGUI()
{
    playPauseButton = std::make_unique<PlayerGUIButton>(PlayerGUIButton::ControlType::play);
    nextButton = std::make_unique<PlayerGUIButton>(PlayerGUIButton::ControlType::next);
    previousButton = std::make_unique<PlayerGUIButton>(PlayerGUIButton::ControlType::last);
    
    //artworkDisplayer = std::make_unique<ImageComponent>();
    
    addAndMakeVisible(playPauseButton.get());
    playPauseButton->setComponentID("player_play_button");
    playPauseButton->addListener(AudioFileStandardiserApplication::getMediator());
    
    addAndMakeVisible(nextButton.get());
    nextButton->setComponentID("player_next_button");
    nextButton->addListener(AudioFileStandardiserApplication::getMediator());
    
    addAndMakeVisible(previousButton.get());
    previousButton->setComponentID("player_last_button");
    previousButton->addListener(AudioFileStandardiserApplication::getMediator());
    
    //addAndMakeVisible(artworkDisplayer.get());
    
    setSize(260, 275);
}

AudioPlayerGUI::~AudioPlayerGUI()
{
    //std::cout << "APGUI Deleted" << std::endl;
}

void AudioPlayerGUI::paint (Graphics& g)
{
    g.fillAll(Colours::lightgrey);
}

void AudioPlayerGUI::resized()
{
    playPauseButton->setBounds(getWidth()/2 - 20, (getHeight()/3) * 2 - 20, 40, 40);
    nextButton->setBounds(getWidth()/4 * 3 - 15, (getHeight()/3) * 2 - 15, 30, 30);
    previousButton->setBounds(getWidth()/4 - 15, (getHeight()/3) * 2 - 15, 30, 30);
    
    //artworkDisplayer->setBounds(20, 20, getWidth()-40, getWidth()-40);
}

void AudioPlayerGUI::changePlayButtonState(bool state)
{
    playPauseButton->changeFunction(PlayerGUIButton::ControlType(state));
}

bool AudioPlayerGUI::getPlayButtonState()
{
    return bool(playPauseButton->getFunction());
}

void AudioPlayerGUI::setArtworkToShow(const Image& artworkImage)
{
    //artworkDisplayer->setImage(artworkImage);
}
