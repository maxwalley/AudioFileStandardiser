/*
  ==============================================================================

    TableModel.h
    Created: 26 Jun 2020 4:50:16pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TableCellComponent.h"
#include "LookAndFeels.h"

class TableModel    :   public TableListBoxModel
{
public:
    TableModel();
    ~TableModel();
    
private:
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    //Vector used for setting null look and feels
    std::vector<TableTextEditorComponent*> componentWeakPointers;
    
    std::unique_ptr<TableTextEditorLAndF> textEditorDrawer;
};
