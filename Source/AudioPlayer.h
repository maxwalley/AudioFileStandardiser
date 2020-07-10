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

class AudioPlayerWindow :   public DocumentWindow
{
public:
    AudioPlayerWindow();
    ~AudioPlayerWindow();
    
    void closeButtonPressed() override;
    
private:
    
};

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
    
    void play();
    void stop();
    void pause();
    
    bool isPlayerPaused() const;
    
    void addListener(AudioPlayerListener* listener);
    
private:
    void timerCallback() override;
    
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transport;
    
    TransportState currentState;
    
    double pausePosition;
    
    std::vector<AudioPlayerListener*> listeners;
    
    bool fileLoaded;
};
