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

void NewMainComponent::paintOverChildren (Graphics& g)
{
    if(fileDrag)
    {
        g.setColour(Colours::silver);
        g.setOpacity(0.7);
        g.fillAll();
        
        Font fontToUse(25);
        String addText("Drop Files To Add");
        int textWidth = fontToUse.getStringWidth(addText);
        
        g.setColour(Colours::black);
        g.setFont(fontToUse);
        g.drawText(addText, getWidth() / 2 - textWidth / 2, getHeight() / 2 - fontToUse.getHeight() / 2, textWidth, fontToUse.getHeight(), Justification::centred);
    }
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
        int tableHeight = table.getHeaderHeight() + AudioFileStandardiserApplication::getMediator()->getNumberOfRowsToDisplay() * table.getRowHeight() + 8;
        
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
            setSize(tableWidth, tableHeight);
            
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

int NewMainComponent::getDisplayedComponents() const
{
    return currentComponents;
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

NewMainComponent::Listener::Listener()
{
    
}

NewMainComponent::Listener::~Listener()
{
    
}

void NewMainComponent::addListener(Listener* newListener)
{
    listeners.push_back(newListener);
}

void NewMainComponent::removeListener(Listener* lisToRemove)
{
    std::remove(listeners.begin(), listeners.end(), lisToRemove);
}

bool NewMainComponent::isInterestedInFileDrag(const StringArray& files)
{
    AudioFileStandardiserApplication::getMediator()->getSupportedFileTypes();
    
    //As long as one file is acceptable then we are interested
    return std::for_each(files.begin(), files.end(), [](const String& str)
    {
        int lastStop = str.lastIndexOf(".");
        
        //If its a folder
        if(lastStop == -1)
        {
            return true;
        }
        
        String fileType = str.substring(lastStop);
        
        if(AudioFileStandardiserApplication::getMediator()->getSupportedFileTypes().contains(fileType))
        {
            return true;
        }
        
        return false;
    });
}

void NewMainComponent::fileDragEnter(const StringArray& files, int x, int y)
{
    fileDrag = true;
    repaint();
}

void NewMainComponent::fileDragExit(const StringArray& files)
{
    fileDrag = false;
    repaint();
}

void NewMainComponent::filesDropped(const StringArray& files, int x, int y)
{
    std::for_each(listeners.begin(), listeners.end(), [&files](Listener* lis)
    {
        lis->filesDropped(files);
    });
    
    fileDrag = false;
    repaint();
}
