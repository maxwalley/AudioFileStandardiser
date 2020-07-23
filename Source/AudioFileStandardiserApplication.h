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

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    /*class MainWindow    : public DocumentWindow
    {
    public:
		MainWindow(String name);

		void closeButtonPressed() override;

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */
	
    /*private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };*/

private:
    std::unique_ptr<Mediator> mediator;
    //std::unique_ptr<MainWindow> mainWindow;
};
