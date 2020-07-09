/*
  ==============================================================================

    AudioPlayerListener.h
    Created: 8 Jul 2020 2:58:54pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "AudioPlayer.h"

class AudioPlayerListener
{
public:
    AudioPlayerListener(){};
    virtual ~AudioPlayerListener(){};
    
    virtual void playerFinished(AudioPlayer* playerThatHasFinished){};
    
};
