/*
  ==============================================================================

    AudioPlayerImplementation.h
    Created: 7 Jul 2020 7:12:49pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class AudioPlayerListener;

class AudioPlayer   :   public AudioAppComponent,
                        public Timer
{
public:
    enum class TransportState
    {
        playing,
        stopped,
        paused
    };
    
    AudioPlayer();
    ~AudioPlayer();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    
    bool isFileLoaded() const;
    void loadFile(const File& fileToPlay);
    
    TransportState getPlayerState();
    
    void play();
    void stop();
    void pause();
    
    void addListener(AudioPlayerListener* listener);
    
    void setGain(float newGain);
    float getGain() const;
    
    double getCurrentPos() const;
    double getPosAsPercentageOfTrackLen() const;
    double getCurrentTrackLength() const;
    double getNumberOfSecondsLeft() const;
    
    //Player index used for distinguishing one player from another - useful for its listener funcs
    void setPlayerIndex(int newIndex);
    int getPlayerIndex() const;
    
private:
    int playerIndex;
    
    void timerCallback() override;
    
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transport;
    
    TransportState currentState;
    
    double pausePosition;
    
    std::vector<AudioPlayerListener*> listeners;
    
    bool fileLoaded;
};
