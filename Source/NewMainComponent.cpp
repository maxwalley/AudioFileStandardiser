/*
  ==============================================================================

    NewMainComponent.cpp
    Created: 24 Jun 2020 8:15:51pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NewMainComponent.h"
#include "AudioFileStandardiserApplication.h"

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
    table.addMouseListener(AudioFileStandardiserApplication::getMediator(), true);

    table.setModel(AudioFileStandardiserApplication::getMediator()->getTableModel());
    
    renameControls = AudioFileStandardiserApplication::getMediator()->getBatchControls();
    fileControls = AudioFileStandardiserApplication::getMediator()->getFileAndDirectoryControls();
    
    addAndMakeVisible(renameControls);
    addAndMakeVisible(fileControls);
    addAndMakeVisible(extraInfoViewport);
    
    tablePopup.addItem(1, "Play", true, false);
    tablePopup.addItem(2, "Extra Info", true, false);
}

NewMainComponent::~NewMainComponent()
{
    //To stop an error in look and feel
    /*for(int j = 1; j < table.getHeader().getNumColumns(false); j++)
    {
        for(int i = 0; i < AudioFileStandardiserApplication::getMediator()->getNumberOfRowsToDisplay(); i++)
        {
            Component* currentComponent = table.getCellComponent(j, i);
            
            if(currentComponent != nullptr)
            {
                currentComponent->setLookAndFeel(nullptr);
            }
        }
    }*/
    
    //Mediator::closeInstance();
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
    else
    {
        int tableHeight = table.getHeaderHeight() + (AudioFileStandardiserApplication::getMediator()->getNumberOfRowsToDisplay() * table.getRowHeight());
        int tableWidth;
        
        if(tableHeight > 530)
        {
            tableWidth = 658;
            tableHeight = 530;
        }
        else
        {
            tableWidth = 650;
        }
        
        table.setBounds(0, 0, tableWidth, tableHeight);
        
        //Table is viewable only
        if(currentComponents == 1)
        {
            setSize(tableWidth, tableHeight + 70);
        }
        //Table is not alone
        else
        {
            setSize(tableWidth + 200, tableHeight + 70);
            
            extraInfoViewport.setBounds(tableWidth, 0, 200, getHeight());
            
            //Batch controls Viewable
            if(currentComponents & RenameControls)
            {
                extraInfoViewport.setViewedComponent(renameControls, false);
                renameControls->setSize(190, 900);
            }
            
            //File and dir controls viewable
            if(currentComponents & FileAndFolderControls)
            {
                extraInfoViewport.setViewedComponent(fileControls, false);
                fileControls->setSize(190, 330);
            }
            
        }
    }
}

void NewMainComponent::setComponentsToDisplay(int components)
{
    currentComponents = componentsToDisplay(components);
}

void NewMainComponent::updateTable()
{
    table.updateContent();
}

int NewMainComponent::showTablePopup()
{
    return tablePopup.show();
}

void NewMainComponent::setAdditionalAudioSource(AudioSource* newAudioSource)
{
    additionalAudioSource = newAudioSource;
}
