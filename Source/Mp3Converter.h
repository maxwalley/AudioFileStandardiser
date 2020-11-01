/*
  ==============================================================================

    Mp3Converter.h
    Created: 1 Nov 2020 6:02:16pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Mp3Converter
{
public:
    Mp3Converter();
    ~Mp3Converter();
    
private:
    LAMEEncoderAudioFormat mp3Encoder;
};
