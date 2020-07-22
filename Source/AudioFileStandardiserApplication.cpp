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

	mainWindow.reset(new MainWindow(getApplicationName()));

	mediator->initialiseComponents();

	mainWindow->setContentNonOwned(mediator->getMainComponent(), true);
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

AudioFileStandardiserApplication::MainWindow::MainWindow(String name) : DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons)
{
	setUsingNativeTitleBar(true);

	setResizable(true, true);
	centreWithSize(getWidth(), getHeight());

	setVisible(true);
}

void AudioFileStandardiserApplication::MainWindow::closeButtonPressed()
{
	JUCEApplication::getInstance()->systemRequestedQuit();
}