/*
  ==============================================================================

    Mediator.cpp
    Created: 22 Jun 2020 3:22:25pm
    Author:  Max Walley

  ==============================================================================
*/

#include "Mediator.h"

Mediator* Mediator::instance = 0;

Mediator* Mediator::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Mediator();
    }
    
    return instance;
}

Mediator::~Mediator()
{
    if(instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

void Mediator::actionListenerCallback (const String &message)
{
    
}

void Mediator::buttonClicked(Button* button)
{
    if(button->getComponentID().compare("intro_openSourceButton") == 0)
    {
        
    }
}
