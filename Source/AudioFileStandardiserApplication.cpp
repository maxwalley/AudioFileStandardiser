/*
  ==============================================================================

    AudioFileStandardiserApplication.cpp
    Created: 13 Jul 2020 10:45:28am
    Author:  Max Walley

  ==============================================================================
*/

#include "AudioFileStandardiserApplication.h"

AudioFileStandardiserApplication::AudioFileStandardiserApplication()
{

}

AudioFileStandardiserApplication::~AudioFileStandardiserApplication()
{

}

const String AudioFileStandardiserApplication::getApplicationName()
{
	return ProjectInfo::projectName;
}

const String AudioFileStandardiserApplication::getApplicationVersion()
{
	return ProjectInfo::versionString;
}

bool AudioFileStandardiserApplication::moreThanOneInstanceAllowed()
{
	return true;
}

void AudioFileStandardiserApplication::initialise(const String& commandLine)
{
	mediator = std::make_unique<Mediator>();

	mediator->initialiseComponents();
    
    testWin = std::make_unique<ComponentWindow>("test", juce::Colours::green, 7);
    testCom = std::make_unique<ComponentListComponent>();
    
    testCom->setSize(200, 400);
    testWin->setContentNonOwned(testCom.get(), true);
    testWin->setVisible(true);
    
    for(int i = 0; i < 100; ++i)
    {
        testCom->addComponent(std::make_unique<TestCom>());
    }
}

void AudioFileStandardiserApplication::shutdown()
{
	
}

void AudioFileStandardiserApplication::systemRequestedQuit()
{
	quit();
}

Mediator* AudioFileStandardiserApplication::getMediatorInstance()
{
	return mediator.get();
}

Mediator* AudioFileStandardiserApplication::getMediator()
{
	AudioFileStandardiserApplication* thisApp = dynamic_cast<AudioFileStandardiserApplication*>(AudioFileStandardiserApplication::getInstance());
	return thisApp->getMediatorInstance();
}
