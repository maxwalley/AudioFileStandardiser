/*
  ==============================================================================

    Mediator.h
    Created: 22 Jun 2020 3:22:25pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Logger.h"
#include "FileInitialiser.h"
#include "DataHandler.h"

class NewMainComponent;

class Mediator  :   public ActionListener,
                    public Button::Listener
{
public:
    
    static Mediator* getInstance();
    
    static void closeInstance();
    
    static NewMainComponent* getMainComponent();
    
private:
    Mediator(){};
    
    static Mediator* instance;
    
    void actionListenerCallback (const String &message) override;
    
    void buttonClicked(Button* button) override;
    
    FileInitialiser initialiser;
    DataHandler dataHandler;
    
    static NewMainComponent* mainComponent;
};
