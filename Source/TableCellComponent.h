/*
  ==============================================================================

    TableCellComponent.h
    Created: 2 Jun 2020 5:20:22pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TableCellComponent
{
public:
    TableCellComponent();
    ~TableCellComponent();
    
    int getColumnID() const;
    int getRowNumber() const;
    
    void setLocationInTable(int column, int row);
    
protected:
    int columnID;
    int rowNumber;
};

class TableTextEditorComponent  :   public TableCellComponent, public TextEditor
{
public:
};

class TableToggleButtonComponent  :   public TableCellComponent, public ToggleButton
{
public:
};
