/*
  ==============================================================================

    PlayControlButton.h
    Created: 22 Dec 2019 6:58:56pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/** A component button class for drawing multiple types of audio player buttons. 
*/
class PlayerGUIButton    : public Button
{
public:
    enum class ControlType
    {
        play,
        pause,
        stop,
        next,
        last
    };
    
    /**Constructor
     
     @param function            the function this button will represent
     */
    PlayerGUIButton(ControlType function);
    
    /**Destructor*/
    ~PlayerGUIButton();

    /**Implementation of the JUCE Component method*/
    void paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
    /**Changes the function this button represents
     
     @param newFunction         the new function this button should represent
     */
    void changeFunction(ControlType newFunction);
    
    /**Returns the function this button represents
     
     @return the function this button represents
     
     @see changeFunction
     */
    ControlType getFunction() const;
    
private:
    
    ControlType buttonFunc;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerGUIButton)
};
