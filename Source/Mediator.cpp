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
    menu = std::make_unique<MenuModel>();
    menu->addActionListener(this);
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
        return dataHandler.numEntries() + 1;
    }
    return 0;
}

String Mediator::getDataForCell(int rowNumber, int column)
{
    if(rowNumber < getNumberOfRowsToDisplay() - 1)
    {
        return dataHandler.getDataForItem(DataHandler::DataConcerned(column), rowNumber);
    }
    return dataHandler.getSimilarDataForSelectedItems(DataHandler::DataConcerned(column));
}

bool Mediator::getSelectedForRow(int rowNumber)
{
    return dataHandler.getItemSelection(rowNumber);
}

void Mediator::actionListenerCallback (const String &message)
{
    if(message.compare("menu_add_files") == 0)
    {
        addNewFiles();
        mainComponent->resized();
    }
}

void Mediator::buttonClicked(Button* button)
{
    if(button->getComponentID().compare("intro_openSourceButton") == 0)
    {
        addNewFiles();
        mainComponent->setComponentToDisplay(NewMainComponent::Table);
        mainComponent->resized();
    }
    
    else if(button->getComponentID().compare("table_button") == 0)
    {
        TableToggleButtonComponent* tempButton = dynamic_cast<TableToggleButtonComponent*>(button);
        
        if(tempButton->getRowNumber() < getNumberOfRowsToDisplay() - 1)
        {
            dataHandler.setItemSelection(tempButton->getRowNumber(), tempButton->getToggleState());
        }
        else
        {
            dataHandler.setAllItemsSelection(tempButton->getToggleState());
        }
        
        mainComponent->updateTable();
    }
}

void Mediator::textEditorTextChanged(TextEditor& editor)
{
    if(editor.getComponentID().compare("table_editor") == 0)
    {
        TableTextEditorComponent& tempEditor = dynamic_cast<TableTextEditorComponent&>(editor);
        
        if(tempEditor.getRowNumber() < getNumberOfRowsToDisplay() - 1)
        {
            dataHandler.setDataForItem(DataHandler::DataConcerned(tempEditor.getColumnID()), tempEditor.getRowNumber(), tempEditor.getText());
        }
        
        else if(tempEditor.getRowNumber() == getNumberOfRowsToDisplay() - 1)
        {
            dataHandler.setDataForSelectedItems(DataHandler::DataConcerned(tempEditor.getColumnID()), true, tempEditor.getText());
        }
        
        mainComponent->updateTable();
    }
}

void Mediator::addNewFiles()
{
    if(initialiser.lookForNewFiles())
    {
        dataHandler.addData(initialiser.getResult());
        initialiser.clearCurrentFiles();
        dataHandler.sort();
        //dataHandler.printTest();
    }
}
