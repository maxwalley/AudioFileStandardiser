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


//==============================================================================
/*
*/
class AudioPlayerGUI    :   public Component
{
public:
    AudioPlayerGUI();
    ~AudioPlayerGUI();

    void paint(Graphics&) override;
    
    void paintOverChildren(Graphics& g) override;
    
    void resized() override;

    void setPlayButtonState(PlayerGUIButton::ControlType state);
    
    PlayerGUIButton::ControlType getPlayButtonState() const;
    
    void setArtworkToShow(const Image& artworkImage);
    
    void setTitleLabelText(const String& newText);
    
    void setPercentageThroughTrack(float newPercentage);
    
private:
    
    std::unique_ptr<PlayerGUIButton> playPauseButton;
    std::unique_ptr<PlayerGUIButton> nextButton;
    std::unique_ptr<PlayerGUIButton> previousButton;
    
    std::unique_ptr<ImageComponent> artworkDisplayer;
    
    std::unique_ptr<Slider> volumeSlider;
    
    std::unique_ptr<Label> titleLabel;
    
    float percentageThroughTrack;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerGUI)
};
