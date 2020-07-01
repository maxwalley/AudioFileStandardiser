/*
  ==============================================================================

    NewMainComponent.cpp
    Created: 24 Jun 2020 8:15:51pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NewMainComponent.h"

//==============================================================================
NewMainComponent::NewMainComponent()    :   currentComponents(Intro)
{
    setSize(introComponent.getWidth(), introComponent.getHeight());
    
    addAndMakeVisible(introComponent);
    
    addAndMakeVisible(table);
    table.setHeader(new TableHeaderComponent);
    table.getHeader().addColumn("Track", 1, 50, 50, 50, 1);
    table.getHeader().addColumn("Track Name", 2, 150, 150, 150, 1);
    table.getHeader().addColumn("Artist Name", 3, 150, 150, 150, 1);
    table.getHeader().addColumn("Album Name", 4, 150, 150, 150, 1);
    table.getHeader().addColumn("Year", 5, 50, 50, 50, 1);
    table.getHeader().addColumn("File Type", 6, 50, 50, 50, 1);
    table.getHeader().addColumn("Selected", 7, 50, 50, 50, 1);
    
    table.setModel(Mediator::getInstance()->getTableModel());
}

NewMainComponent::~NewMainComponent()
{
    //To stop an error in look and feel
    for(int j = 1; j < table.getHeader().getNumColumns(false); j++)
    {
        for(int i = 0; i < Mediator::getInstance()->getNumberOfRowsToDisplay(); i++)
        {
            Component* currentComponent = table.getCellComponent(j, i);
            
            if(currentComponent != nullptr)
            {
                currentComponent->setLookAndFeel(nullptr);
            }
        }
    }
    
    Mediator::closeInstance();
}

void NewMainComponent::paint (Graphics& g)
{
    
}

void NewMainComponent::resized()
{
    //Intro component is viewable
    if(currentComponents == 0)
    {
        introComponent.setBounds(0, 0, getWidth(), getHeight());
    }
    
    //Table is viewable
    else if(currentComponents % 1 == 0)
    {
        int tableHeight = table.getHeaderHeight() + (Mediator::getInstance()->getNumberOfRowsToDisplay() * table.getRowHeight());
        
        //Adjusts width and height to deal with the scroll bar
        if(tableHeight > 600)
        {
            setSize(658, 600);
            table.setBounds(0, 0, 658, getHeight());
        }
        else
        {
            setSize(650, tableHeight);
            table.setBounds(0, 0, 650, getHeight());
        }
    }
}

void NewMainComponent::setComponentToDisplay(componentsToDisplay component)
{
    currentComponents = component;
}

void NewMainComponent::updateTable()
{
    table.updateContent();
}
