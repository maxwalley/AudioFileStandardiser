/*
  ==============================================================================

    NewMainComponent.cpp
    Created: 24 Jun 2020 8:15:51pm
    Author:  Max Walley

  ==============================================================================
*/

//#include "../JuceLibraryCode/JuceHeader.h"
#include "NewMainComponent.h"
#include "AudioFileStandardiserApplication.h"

//==============================================================================
NewMainComponent::NewMainComponent()    :   currentComponents(Intro)
{
    setSize(introComponent.getWidth(), introComponent.getHeight());
    
    addAndMakeVisible(introComponent);
    
    addAndMakeVisible(table);
    table.setHeader(std::make_unique<TableHeaderComponent>());
    table.getHeader().addColumn("Track", 1, 50, 50, 50, 13);
    table.getHeader().addColumn("Track Name", 2, 150, 150, 150, 13);
    table.getHeader().addColumn("Artist Name", 3, 150, 150, 150, 13);
    table.getHeader().addColumn("Album Name", 4, 150, 150, 150, 13);
    table.getHeader().addColumn("Year", 5, 50, 50, 50, 13);
    table.getHeader().addColumn("File Type", 6, 50, 50, 50, 13);
    table.getHeader().addColumn("File Name", 7, 150, 150, 150, 12);
    table.getHeader().addColumn("Length", 8, 50, 50, 50, 12);
    table.getHeader().addColumn("Selected", 100, 50, 50, 50, 13);
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
        int tableHeight = table.getHeaderHeight() + ((AudioFileStandardiserApplication::getMediator()->getNumberOfRowsToDisplay() + 1) * table.getRowHeight()) + 8;
        
        int tableWidth = table.getHeader().getTotalWidth() + 8;
        
        currentLimits.maxHeight = tableHeight;
        
        currentLimits.minWidth = 100;
        
        if(table.getHorizontalScrollBar().isVisible())
        {
            currentLimits.minHeight = 80;
        }
        else
        {
            currentLimits.minHeight = 72;
        }
        
        //Table is viewable only
        if(currentComponents == 1)
        {
            table.setBounds(0, 0, getWidth(), getHeight());
            
            currentLimits.maxWidth = tableWidth;
            
            if(tableWidth > 650)
            {
                currentLimits.defWidth = 658;
            }
            else
            {
                currentLimits.defWidth = tableWidth;
            }
            
            if(tableHeight > 530)
            {
                currentLimits.defHeight = 530;
            }
            else
            {
                currentLimits.defHeight = tableHeight;
            }
        }
        
        //Table is not alone
        else
        {
            setSize(tableWidth + 200, tableHeight);
            
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

NewMainComponent::SizeLimits NewMainComponent::getCurrentSizeLimits() const
{
    return currentLimits;
}
