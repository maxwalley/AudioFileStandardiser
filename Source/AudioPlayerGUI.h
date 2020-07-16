/*
  ==============================================================================

    AudioPlayerGUI.h
    Created: 7 Jul 2020 3:37:27pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayerGUIButton.h"
#include "ChronoTimeToStringConverter.h"


//==============================================================================
/*
*/
class PartiallyFilledRect   :   public Component
{
public:
    PartiallyFilledRect(float percentage = 0.0);
    ~PartiallyFilledRect();
    
    void paint(Graphics& g) override;
    
    void setPercentageToFill(float newPercentage);
    float getPercentageToFill() const;
    
private:
    float percentageToFill;
};

class AudioPlayerGUI    :   public Component
{
public:
    AudioPlayerGUI();
    ~AudioPlayerGUI();

    void paint(Graphics&) override;
    
    void resized() override;

    void setPlayButtonState(PlayerGUIButton::ControlType state);
    
    PlayerGUIButton::ControlType getPlayButtonState() const;
    
    void setArtworkToShow(const Image& artworkImage);
    
    void setTitleLabelText(const String& newText);
    
    void setPercentageThroughTrack(float newPercentage);
    
    void setTimeThroughTrack(std::chrono::seconds timeThrough);
    void setLengthOfTrack(std::chrono::seconds trackLen);
    
private:
    
    std::unique_ptr<PlayerGUIButton> playPauseButton;
    std::unique_ptr<PlayerGUIButton> nextButton;
    std::unique_ptr<PlayerGUIButton> previousButton;
    
    std::unique_ptr<ImageComponent> artworkDisplayer;
    
    std::unique_ptr<Slider> volumeSlider;
    
    std::unique_ptr<Label> titleLabel;
    
    std::unique_ptr<PartiallyFilledRect> progressBar;
    
    std::unique_ptr<Label> timeGoneLabel;
    std::unique_ptr<Label> trackLengthLabel;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerGUI)
};
