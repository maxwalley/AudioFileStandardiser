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
    artworkDisplayer = std::make_unique<ImageComponent>();
    volumeSlider = std::make_unique<Slider>();
    titleLabel = std::make_unique<Label>();
    
    addAndMakeVisible(playPauseButton.get());
    playPauseButton->setComponentID("player_play_button");
    playPauseButton->addListener(AudioFileStandardiserApplication::getMediator());
    
    addAndMakeVisible(nextButton.get());
    nextButton->setComponentID("player_next_button");
    nextButton->addListener(AudioFileStandardiserApplication::getMediator());
    
    addAndMakeVisible(previousButton.get());
    previousButton->setComponentID("player_last_button");
    previousButton->addListener(AudioFileStandardiserApplication::getMediator());
    
    addAndMakeVisible(artworkDisplayer.get());
    
    addAndMakeVisible(volumeSlider.get());
    volumeSlider->addListener(AudioFileStandardiserApplication::getMediator());
    volumeSlider->setComponentID("player_vol_slider");
    volumeSlider->setRange(0.0, 1.0);
    volumeSlider->setSliderStyle(Slider::LinearHorizontal);
    volumeSlider->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    volumeSlider->setValue(0.5);
    volumeSlider->setColour(Slider::thumbColourId, Colours::white);
    
    addAndMakeVisible(titleLabel.get());
    titleLabel->setJustificationType(Justification::centred);
    titleLabel->setColour(Label::textColourId, Colours::black);
    
    setSize(300, 450);
}

AudioPlayerGUI::~AudioPlayerGUI()
{
    
}

void AudioPlayerGUI::paint (Graphics& g)
{
    g.fillAll(Colours::lightgrey);
}

void AudioPlayerGUI::resized()
{
    playPauseButton->setBounds(getWidth()/2 - 20, (getHeight()/5) * 4 - 20, 40, 40);
    nextButton->setBounds(getWidth()/4 * 3 - 15, (getHeight()/5) * 4 - 15, 30, 30);
    previousButton->setBounds(getWidth()/4 - 15, (getHeight()/5) * 4 - 15, 30, 30);
    
    artworkDisplayer->setBounds(20, 20, getWidth()-40, getWidth()-40);
    
    volumeSlider->setBounds(20, getHeight()-30, getWidth()-40, 20);
    
    titleLabel->setBounds(20, getWidth() - 10, getWidth()-40, 20);
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
    artworkDisplayer->setImage(artworkImage);
}

void AudioPlayerGUI::setTitleLabelText(const String& newText)
{
    titleLabel->setText(newText, dontSendNotification);
}
