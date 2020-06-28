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

//TableModel Mediator::tableModel;

DataHandler Mediator::dataHandler;

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

void Mediator::initialiseComponents()
{
    tableModel = std::make_unique<TableModel>();
}

TableModel* Mediator::getTableModel()
{
    return tableModel.get();
}

DataHandler* Mediator::getDataHandler()
{
    return &dataHandler;
}

int Mediator::getNumberOfRowsToDisplay()
{
    int numEntries = dataHandler.numEntries();
    
    if(numEntries != 0)
    {
        return dataHandler.numEntries();
    }
    return 0;
}

String Mediator::getDataForCell(int rowNumber, int column)
{
    return dataHandler.getDataForItem(DataHandler::DataConcerned(column), rowNumber);
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
            //dataHandler.printTest();
            
            mainComponent->setComponentToDisplay(NewMainComponent::Table);
            mainComponent->resized();
        }
    }
}

void Mediator::textEditorTextChanged(TextEditor& editor)
{
    
}
