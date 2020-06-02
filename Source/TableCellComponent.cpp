/*
  ==============================================================================

    TableCellComponent.cpp
    Created: 2 Jun 2020 5:20:22pm
    Author:  Max Walley

  ==============================================================================
*/

#include "TableCellComponent.h"

TableCellComponent::TableCellComponent()
{
    
}

TableCellComponent::~TableCellComponent()
{
    
}

int TableCellComponent::getColumnID() const
{
    return columnID;
}

int TableCellComponent::getRowNumber() const
{
    return rowNumber;
}

void TableCellComponent::setLocationInTable(int column, int row)
{
    columnID = column;
    rowNumber = row;
}
