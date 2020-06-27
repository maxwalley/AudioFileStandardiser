/*
  ==============================================================================

    TableModel.cpp
    Created: 26 Jun 2020 4:50:16pm
    Author:  Max Walley

  ==============================================================================
*/

#include "TableModel.h"
#include "Mediator.h"

TableModel::TableModel()
{
    //textEditorDrawer = new TableTextEditorLAndF();
}

TableModel::~TableModel()
{
    //delete textEditorDrawer;
    
    for (int i = 0; i < getNumRows(); i++)
    {
        
    }
}
    
int TableModel::getNumRows()
{
    return 0;
}

void TableModel::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if(rowNumber % 2 == 0)
    {
        g.fillAll(Colours::blue);
    }
    else
    {
        g.fillAll(Colours::red);
    }
    
}

void TableModel::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    
}

Component* TableModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
{
    //If no component currently exists
    if(existingComponentToUpdate == nullptr)
    {
        if(columnId == 7)
        {
            TableToggleButtonComponent* componentToAdd = new TableToggleButtonComponent();
            componentToAdd->addListener(Mediator::getInstance());
            componentToAdd->setLocationInTable(columnId, rowNumber);
            //Sets the name for identification by a listener
            componentToAdd->setComponentID("table_button");
            return componentToAdd;
        }
        
        TableTextEditorComponent* componentToAdd = new TableTextEditorComponent();
        componentToAdd->addListener(Mediator::getInstance());
        componentToAdd->setLocationInTable(columnId, rowNumber);
        componentToAdd->setColour(TextEditor::textColourId, Colours::black);
        componentToAdd->setColour(TextEditor::outlineColourId, Colours::black);
        //componentToAdd->setLookAndFeel(textEditorDrawer);
        
        if(rowNumber % 2 == 0)
        {
            componentToAdd->setColour(TextEditor::backgroundColourId, Colours::silver);
        }
        else
        {
            componentToAdd->setColour(TextEditor::backgroundColourId, Colours::lightgrey);
        }
        
        if((columnId == 1 || columnId == 5) && columnId != 6)
        {
            componentToAdd->setJustification(Justification::centred);
            componentToAdd->setInputRestrictions(0, "0123456789");
        }
        else
        {
            componentToAdd->setJustification(Justification::left);
        }
        
        if(columnId == 6)
        {
            componentToAdd->setJustification(Justification::centred);
            componentToAdd->setEnabled(false);
        }
        
        return componentToAdd;
    }
}
