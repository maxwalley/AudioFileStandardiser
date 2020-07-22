/*
  ==============================================================================

    TableModel.cpp
    Created: 26 Jun 2020 4:50:16pm
    Author:  Max Walley

  ==============================================================================
*/

#include "TableModel.h"
#include "AudioFileStandardiserApplication.h"

TableModel::TableModel()
{
    textEditorDrawer = std::make_shared<TableTextEditorLAndF>();
}

TableModel::~TableModel()
{
    
}
    
int TableModel::getNumRows()
{
    return AudioFileStandardiserApplication::getMediator()->getNumberOfRowsToDisplay();
}

void TableModel::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if(rowNumber % 2 == 0)
    {
        g.fillAll(Colours::silver);
    }
    else
    {
        g.fillAll(Colours::lightgrey);
    }
    g.drawLine(0, height, width, height);
}

void TableModel::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    
}

Component* TableModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
{
    //If no component currently exists
    if(existingComponentToUpdate == nullptr)
    {
        if(columnId == 100)
        {
            TableToggleButtonComponent* componentToAdd = new TableToggleButtonComponent();
            componentToAdd->addListener(AudioFileStandardiserApplication::getMediator());
            componentToAdd->setLocationInTable(columnId, rowNumber);
            //Sets the name for identification by a listener
            componentToAdd->setComponentID("table_button");
            return componentToAdd;
        }
        
        TableTextEditorComponent* componentToAdd = new TableTextEditorComponent();
        componentToAdd->addListener(AudioFileStandardiserApplication::getMediator());
        componentToAdd->setPopupMenuEnabled(false);
        //Sets the name for identification by a listener
        componentToAdd->setComponentID("table_editor");
        componentToAdd->setLocationInTable(columnId, rowNumber);
        componentToAdd->setColour(TextEditor::textColourId, Colours::black);
        componentToAdd->setColour(TextEditor::outlineColourId, Colours::black);
        componentToAdd->setLookAndFeel(textEditorDrawer.get());
        
        if(rowNumber % 2 == 0)
        {
            componentToAdd->setColour(TextEditor::backgroundColourId, Colours::silver);
        }
        else
        {
            componentToAdd->setColour(TextEditor::backgroundColourId, Colours::lightgrey);
        }
        
        //Justification
        if(columnId == 1 || columnId == 5 || columnId == 6)
        {
            componentToAdd->setJustification(Justification::centred);
        }
        else
        {
            componentToAdd->setJustification(Justification::left);
        }
        
        //Enabled/input restrictions
        if(columnId == 6 || columnId == 8)
        {
            componentToAdd->setEnabled(false);
        }
        else if(columnId == 1 || columnId == 5)
        {
            componentToAdd->setInputRestrictions(0, "0123456789");
        }
        
        return componentToAdd;
    }
    
    //If a component is already there
    if(columnId != 100)
    {
        //Casts the component to the table specific class
        TableTextEditorComponent* componentToUpdate = dynamic_cast<TableTextEditorComponent*>(existingComponentToUpdate);
            
        componentToUpdate->setLocationInTable(columnId, rowNumber);
    
        if(rowNumber < getNumRows())
        {
            componentToUpdate->setText(AudioFileStandardiserApplication::getMediator()->getDataForCell(rowNumber, columnId), dontSendNotification);
            
            return componentToUpdate;
        }
    }
    
    //If column id is 7
    if(rowNumber < getNumRows() -1)
    {
        TableToggleButtonComponent* componentToUpdate = dynamic_cast<TableToggleButtonComponent*>(existingComponentToUpdate);
        
        componentToUpdate->setToggleState(AudioFileStandardiserApplication::getMediator()->getSelectedForRow(rowNumber), dontSendNotification);
        
        return componentToUpdate;
    }
    
    return existingComponentToUpdate;
}
