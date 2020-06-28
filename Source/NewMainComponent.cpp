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
    
    Mediator::getInstance()->initialiseComponents();
    
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
        setSize(650, 300);
        table.setBounds(0, 0, 650, 300);
    }
}

void NewMainComponent::setComponentToDisplay(componentsToDisplay component)
{
    currentComponents = component;
}
