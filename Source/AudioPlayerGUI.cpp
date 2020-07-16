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
PartiallyFilledRect::PartiallyFilledRect(float percentage)  :   percentageToFill(percentage)
{
    
}

PartiallyFilledRect::~PartiallyFilledRect()
{
    
}

void PartiallyFilledRect::paint(Graphics& g)
{
    g.setColour(Colours::grey);
    g.fillRect(0.0, 0.0, float(getWidth())/100.0 * percentageToFill, float(getHeight()));
}

void PartiallyFilledRect::setPercentageToFill(float newPercentage)
{
    if(newPercentage > 0 && newPercentage < 100)
    {
        percentageToFill = newPercentage;
    }
}

float PartiallyFilledRect::getPercentageToFill() const
{
    return percentageToFill;
}


AudioPlayerGUI::AudioPlayerGUI()
{
    playPauseButton = std::make_unique<PlayerGUIButton>(PlayerGUIButton::ControlType::play);
    nextButton = std::make_unique<PlayerGUIButton>(PlayerGUIButton::ControlType::next);
    previousButton = std::make_unique<PlayerGUIButton>(PlayerGUIButton::ControlType::last);
    artworkDisplayer = std::make_unique<ImageComponent>();
    volumeSlider = std::make_unique<Slider>();
    titleLabel = std::make_unique<Label>();
    progressBar = std::make_unique<PartiallyFilledRect>();
    timeGoneLabel = std::make_unique<Label>();
    trackLengthLabel = std::make_unique<Label>();
    
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
    
    addAndMakeVisible(progressBar.get());
    progressBar->addMouseListener(AudioFileStandardiserApplication::getMediator(), true);
    progressBar->setComponentID("playerGUI_prog_bar");
    
    addAndMakeVisible(timeGoneLabel.get());
    timeGoneLabel->setJustificationType(Justification::centred);
    timeGoneLabel->setColour(Label::textColourId, Colours::black);
    timeGoneLabel->setFont(Font(13));
    addAndMakeVisible(trackLengthLabel.get());
    trackLengthLabel->setJustificationType(Justification::centred);
    trackLengthLabel->setColour(Label::textColourId, Colours::black);
    trackLengthLabel->setFont(Font(13));
    
    timeGoneLabel->setText("test", dontSendNotification);
    trackLengthLabel->setText("test", dontSendNotification);
    
    setSize(300, 450);
}

AudioPlayerGUI::~AudioPlayerGUI()
{
    
}

void AudioPlayerGUI::paint(Graphics& g)
{
    g.fillAll(Colours::lightgrey);
}

void AudioPlayerGUI::resized()
{
    playPauseButton->setBounds(getWidth()/2 - 20, getHeight() - 95, 40, 40);
    nextButton->setBounds(getWidth()/4 * 3 - 15, getHeight() - 90, 30, 30);
    previousButton->setBounds(getWidth()/4 - 15, getHeight() - 90, 30, 30);
    
    artworkDisplayer->setBounds(20, 20, getWidth()-40, getWidth()-40);
    
    volumeSlider->setBounds(20, getHeight()-30, getWidth()-40, 20);
    
    titleLabel->setBounds(20, getHeight() - 130, getWidth()-40, 20);
    
    progressBar->setBounds(20, getWidth()-20, getWidth()-40, 10);
    
    timeGoneLabel->setBounds(0, getHeight()-160, 40, 20);
    trackLengthLabel->setBounds(getWidth()-40, getHeight()-160, 40, 20);
}

void AudioPlayerGUI::setPlayButtonState(PlayerGUIButton::ControlType state)
{
    playPauseButton->changeFunction(state);
}

PlayerGUIButton::ControlType AudioPlayerGUI::getPlayButtonState() const
{
    return playPauseButton->getFunction();
}

void AudioPlayerGUI::setArtworkToShow(const Image& artworkImage)
{
    artworkDisplayer->setImage(artworkImage);
}

void AudioPlayerGUI::setTitleLabelText(const String& newText)
{
    titleLabel->setText(newText, dontSendNotification);
}

void AudioPlayerGUI::setPercentageThroughTrack(float newPercentage)
{
    progressBar->setPercentageToFill(newPercentage);
    progressBar->repaint();
}

void AudioPlayerGUI::setTimeThroughTrack(std::chrono::seconds timeThrough)
{
    timeGoneLabel->setText(ChronoTimeToStringConverter::convertToWildcardString("%m:%s", timeThrough), dontSendNotification);
}

void AudioPlayerGUI::setLengthOfTrack(std::chrono::seconds trackLen)
{
    trackLengthLabel->setText(ChronoTimeToStringConverter::convertToWildcardString("%m:%s", trackLen), dontSendNotification);
}
