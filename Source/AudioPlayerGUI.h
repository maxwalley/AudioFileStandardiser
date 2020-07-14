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

    void paint (Graphics&) override;
    void resized() override;

    // 0 for play, 1 for pause
    void changePlayButtonState(bool state);
    
    bool getPlayButtonState();
    
    void setArtworkToShow(const Image& artworkImage);
    
    void setTitleLabelText(const String& newText);
    
private:
    
    std::unique_ptr<PlayerGUIButton> playPauseButton;
    std::unique_ptr<PlayerGUIButton> nextButton;
    std::unique_ptr<PlayerGUIButton> previousButton;
    
    std::unique_ptr<ImageComponent> artworkDisplayer;
    
    std::unique_ptr<Slider> volumeSlider;
    
    std::unique_ptr<Label> titleLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerGUI)
};
