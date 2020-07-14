/*
  ==============================================================================

    AudioPlayerImplementation.cpp
    Created: 7 Jul 2020 7:12:49pm
    Author:  Max Walley

  ==============================================================================
*/

#include "AudioPlayer.h"
#include "AudioPlayerListener.h" 

AudioPlayer::AudioPlayer()  :   currentState(TransportState::stopped), pausePosition(0.0)
{
    formatManager.registerBasicFormats();
    setAudioChannels(0, 2);
}

AudioPlayer::~AudioPlayer()
{
    shutdownAudio();
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transport.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioPlayer::releaseResources()
{
    transport.releaseResources();
}

void AudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    if(!readerSource)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    
    transport.getNextAudioBlock(bufferToFill);
}

bool AudioPlayer::isFileLoaded() const
{
    return fileLoaded;
}

void AudioPlayer::loadFile(const File& fileToPlay)
{
    AudioFormatReader* reader = formatManager.createReaderFor(fileToPlay);
    if(reader != nullptr)
    {
        std::unique_ptr<AudioFormatReaderSource> tempReaderSource = std::make_unique<AudioFormatReaderSource>(reader, true);
        transport.setSource(tempReaderSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(tempReaderSource.release());
        fileLoaded = true;
    }
}

AudioPlayer::TransportState AudioPlayer::getPlayerState()
{
    return currentState;
}

void AudioPlayer::play()
{
    if(fileLoaded)
    {
        if(currentState == TransportState::paused)
        {
            transport.setPosition(pausePosition);
        }
        
        transport.start();
        currentState = TransportState::playing;
        Timer::startTimer(50);
    }
}

void AudioPlayer::stop()
{
    transport.stop();
    currentState = TransportState::stopped;
    Timer::stopTimer();
}

void AudioPlayer::pause()
{
    if(currentState == TransportState::playing)
    {
        pausePosition = transport.getCurrentPosition();
        transport.stop();
        Timer::stopTimer();
        currentState = TransportState::paused;
    }
}

void AudioPlayer::addListener(AudioPlayerListener* listener)
{
    listeners.push_back(listener);
}

void AudioPlayer::setGain(float newGain)
{
    transport.setGain(newGain);
}

float AudioPlayer::getGain() const
{
    return transport.getGain();
}

void AudioPlayer::setPlayerIndex(int newIndex)
{
    playerIndex = newIndex;
}

int AudioPlayer::getPlayerIndex() const
{
    return playerIndex;
}

void AudioPlayer::timerCallback()
{
    if(currentState == TransportState::playing && transport.hasStreamFinished())
    {
        for(int i = 0; i < listeners.size(); i++)
        {
            listeners[i]->playerFinished(this);
        }
    }
}
