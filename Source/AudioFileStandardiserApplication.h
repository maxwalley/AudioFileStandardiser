/*
  ==============================================================================

    AudioFileStandardiserApplication.h
    Created: 13 Jul 2020 10:45:28am
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "NewMainComponent.h"
#include "Mediator.h"

class AudioFileStandardiserApplication  : public JUCEApplication
{
public:
    //==============================================================================
	AudioFileStandardiserApplication();
	~AudioFileStandardiserApplication();

	const String getApplicationName() override;
	const String getApplicationVersion() override;
	bool moreThanOneInstanceAllowed() override;

    //==============================================================================
	void initialise(const String& commandLine) override;

	void shutdown() override;

    //==============================================================================
	void systemRequestedQuit() override;
    
	Mediator* getMediatorInstance();
    
	static Mediator* getMediator();

private:
    std::unique_ptr<Mediator> mediator;
    //std::unique_ptr<MainWindow> mainWindow;
};
