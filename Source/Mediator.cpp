/*
  ==============================================================================

    Mediator.cpp
    Created: 22 Jun 2020 3:22:25pm
    Author:  Max Walley

  ==============================================================================
*/

#include "Mediator.h"

#include "NewMainComponent.h"

Mediator* Mediator::instance = 0;

NewMainComponent* Mediator::mainComponent;

TableModel Mediator::tableModel;

Mediator* Mediator::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Mediator();
    }
    return instance;
}

void Mediator::closeInstance()
{
    if(instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

NewMainComponent* Mediator::getMainComponent()
{
    if(mainComponent == nullptr)
    {
        mainComponent = new NewMainComponent;
    }
    return mainComponent;
}

TableModel* Mediator::getTableModel()
{
    return &tableModel;
}

void Mediator::actionListenerCallback (const String &message)
{
    
}

void Mediator::buttonClicked(Button* button)
{
    if(button->getComponentID().compare("intro_openSourceButton") == 0)
    {
        if(initialiser.lookForNewFiles())
        {
            dataHandler.addData(initialiser.getResult());
            initialiser.clearCurrentFiles();
            dataHandler.sort();
            dataHandler.printTest();
            
            //mainComponent->setComponentToDisplay(NewMainComponent::Table);
            //mainComponent->resized();
        }
    }
}

void Mediator::textEditorTextChanged(TextEditor& editor)
{
    
}
