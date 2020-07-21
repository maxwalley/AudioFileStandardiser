/*
  ==============================================================================

    Mediator.cpp
    Created: 22 Jun 2020 3:22:25pm
    Author:  Max Walley

  ==============================================================================
*/

#include "Mediator.h"

#include "NewMainComponent.h"

Mediator::Mediator()
{
    
}

Mediator::~Mediator()
{
    delete mainComponent;
}

NewMainComponent* Mediator::getMainComponent()
{
    return mainComponent;
}

void Mediator::initialiseComponents()
{
    dataHandler = std::make_unique<DataHandler>();
    tableModel = std::make_unique<TableModel>();
    batchControls = std::make_unique<BatchRenameControls>();
    batchControlsImp = std::make_unique<BatchControlsImplementation>(batchControls.get());
    fileControls = std::make_unique<FileAndDirectoryControls>();
    audioPlayerControls = std::make_unique<AudioPlayerGUI>();
    audioPlayerControls->addKeyListener(this);
    mainComponent = new NewMainComponent();
    menu = std::make_unique<MenuModel>();
    menu->addActionListener(this);
    player = std::make_unique<AudioPlayer>();
    player->addListener(this);
    player->setPlayerIndex(1);
    playerWindow = std::make_unique<ComponentWindow>("Player", Colours::green, DocumentWindow::allButtons);
    playerWindow->setContentNonOwned(audioPlayerControls.get(), true);
    playerWindow->addActionListener(this);
    currentPlayingIndex = -1;
    
}

TableModel* Mediator::getTableModel()
{
    return tableModel.get();
}

DataHandler* Mediator::getDataHandler()
{
    return dataHandler.get();
}

BatchRenameControls* Mediator::getBatchControls()
{
    return batchControls.get();
}

FileAndDirectoryControls* Mediator::getFileAndDirectoryControls()
{
    return fileControls.get();
}

AudioPlayerGUI* Mediator::getAudioPlayerControls()
{
    return audioPlayerControls.get();
}

int Mediator::getNumberOfRowsToDisplay()
{
    int numEntries = dataHandler->numEntries();
    
    if(numEntries != 0)
    {
        return dataHandler->numEntries() + 1;
    }
    return 0;
}

String Mediator::getDataForCell(int rowNumber, int column)
{
    if(rowNumber < getNumberOfRowsToDisplay() - 1)
    {
        return dataHandler->getDataForItem(DataHandler::DataConcerned(column), rowNumber);
    }
    return dataHandler->getSimilarDataForSelectedItems(DataHandler::DataConcerned(column));
}

bool Mediator::getSelectedForRow(int rowNumber)
{
    return dataHandler->getItemSelection(rowNumber);
}

void Mediator::setDataForCell(int rowNumber, int column, const String& newData)
{
    if(rowNumber < getNumberOfRowsToDisplay() -1)
    {
        dataHandler->setDataForItem(DataHandler::DataConcerned(column), rowNumber, newData);
    }
}

void Mediator::actionListenerCallback (const String &message)
{
    if(message.compare("menu_add_files") == 0)
    {
        addNewFiles();
        mainComponent->resized();
        mainComponent->updateTable();
    }
    
    else if(message.compare("menu_show_batch") == 0)
    {
        if(menu->getBatchControlsShown())
        {
            menu->setFileControlsShown(false);
            mainComponent->setComponentsToDisplay(NewMainComponent::Table | NewMainComponent::RenameControls);
        }
        else
        {
            mainComponent->setComponentsToDisplay(NewMainComponent::Table);
        }
        mainComponent->resized();
    }
    
    else if(message.compare("menu_show_file_controls") == 0)
    {
        if(menu->getFileControlsShown())
        {
            menu->setBatchControlsShown(false);
            mainComponent->setComponentsToDisplay(NewMainComponent::Table | NewMainComponent::FileAndFolderControls);
        }
        else
        {
            mainComponent->setComponentsToDisplay(NewMainComponent::Table);
        }
        mainComponent->resized();
    }
    
    else if(message.compare("menu_show_player") == 0)
    {
        showPlayer(menu->getPlayerWindowOpen());
    }
    
    else if(message.compare("Player_closed") == 0)
    {
        stopPlayer();
    }
}

void Mediator::buttonClicked(Button* button)
{
    if(button->getComponentID().compare("intro_openSourceButton") == 0)
    {
        if(addNewFiles())
        {
            mainComponent->setComponentsToDisplay(NewMainComponent::Table);
            mainComponent->resized();
            menu->setMenuItemVisible(MenuModel::MenuNames::View, true);
            menu->setMenuItemVisible(MenuModel::MenuNames::Window, true);
        }
    }
    
    else if(button->getComponentID().compare("table_button") == 0)
    {
        TableToggleButtonComponent* tempButton = dynamic_cast<TableToggleButtonComponent*>(button);
        
        if(tempButton->getRowNumber() < getNumberOfRowsToDisplay() - 1)
        {
            dataHandler->setItemSelection(tempButton->getRowNumber(), tempButton->getToggleState());
        }
        else
        {
            dataHandler->setAllItemsSelection(tempButton->getToggleState());
        }
        
        mainComponent->updateTable();
    }
    
    else if(button->getComponentID().compare("batch_apply") == 0)
    {
        //Iterates through the 3 possible data types that could be edited by batch controls
        for(int i = 0; i < 3; i++)
        {
            int columnId;
            int buttonActive;
            
            //Switches to the relevant data type for this iteration
            switch(i)
            {
                case 0:
                    buttonActive = batchControlsImp->getActiveDataButtons() & BatchRenameControls::titleButton;
                    columnId = 2;
                    break;
                    
                case 1:
                    buttonActive = batchControlsImp->getActiveDataButtons() & BatchRenameControls::artistButton;
                    columnId = 3;
                    break;
                    
                case 2:
                    buttonActive = batchControlsImp->getActiveDataButtons() & BatchRenameControls::albumButton;
                    columnId = 4;
                    break;
            }
            
            //Checks if the button in batch controls for that data type was on
            if(buttonActive != 0)
            {
                for(int i = 0; i < dataHandler->numEntries(); i++)
                {
                    if(dataHandler->getItemSelection(i))
                    {
                        setDataForCell(i, columnId, batchControlsImp->manipulateStringAccordingToGUI(getDataForCell(i, columnId)));
                    }
                }
            }
        }
        mainComponent->updateTable();
    }
    
    else if(button->getComponentID().compare("extra_info_close") == 0)
    {
        menu->setFileControlsShown(false);
        menu->setBatchControlsShown(false);
        mainComponent->setComponentsToDisplay(NewMainComponent::Table);
        mainComponent->resized();
    }
    
    else if(button->getComponentID().compare("file_controls_move") == 0)
    {
        dataHandler->moveSelectedItemsBasedOnWildcards(*fileControls->getNewDirAndWildcardPath(), true);
    }
    
    else if(button->getComponentID().compare("player_play_button") == 0)
    {
        if(player->getPlayerState() == AudioPlayer::TransportState::playing)
        {
            player->pause();
            audioPlayerControls->setPlayButtonState(PlayerGUIButton::ControlType::play);
        }
        else
        {
            playIndex(currentPlayingIndex, false);
        }
    }
    
    else if(button->getComponentID().compare("player_next_button") == 0)
    {
        playIndex(++currentPlayingIndex, true);
    }
    
    else if(button->getComponentID().compare("player_last_button") == 0)
    {
        playIndex(--currentPlayingIndex, true);
    }
}

void Mediator::textEditorTextChanged(TextEditor& editor)
{
    if(editor.getComponentID().compare("table_editor") == 0)
    {
        TableTextEditorComponent& tempEditor = dynamic_cast<TableTextEditorComponent&>(editor);
        
        if(tempEditor.getRowNumber() < getNumberOfRowsToDisplay() - 1)
        {
            setDataForCell(tempEditor.getRowNumber(), tempEditor.getColumnID(), tempEditor.getText());
        }
        
        else if(tempEditor.getRowNumber() == getNumberOfRowsToDisplay() - 1)
        {
            dataHandler->setDataForSelectedItems(DataHandler::DataConcerned(tempEditor.getColumnID()), true, tempEditor.getText());
        }
        
        mainComponent->updateTable();
    }
}

void Mediator::mouseDown(const MouseEvent& event)
{
    if(event.originalComponent->getComponentID().compare("playerGUI_prog_bar") == 0)
    {
        if(event.mods.isLeftButtonDown())
        {
            float percentageAlongClicked = (float(event.getMouseDownX())/float(event.originalComponent->getWidth())) * 100.0;
            
            player->setPosAsPercetageOfTrackLen(percentageAlongClicked);
        }
    }
    
    if(event.originalComponent->getComponentID().compare("table_editor") == 0)
    {
        if(event.mods.isRightButtonDown())
        {
            
            TableCellComponent* originalComponent = dynamic_cast<TableCellComponent*>(event.originalComponent);
            
            if(originalComponent)
            {
                int componentRowNumber = originalComponent->getRowNumber();
        
                if(componentRowNumber != getNumberOfRowsToDisplay() - 1)
                {
                    int menuClicked = mainComponent->showTablePopup();
                
                    //Play option
                    if(menuClicked == 1)
                    {
                        playIndex(componentRowNumber, true);
                        showPlayer(true);
                    }
                
                    //Extra info option
                    else if(menuClicked == 2)
                    {
                        std::cout << "Extra info" << std::endl;
                    }
                }
            }
        }
    }
}

void Mediator::playerFinished(AudioPlayer* playerThatHasFinished)
{
    if(playerThatHasFinished->getPlayerIndex() == 1)
    {
        playIndex(++currentPlayingIndex, true);
    }
}

void Mediator::sliderValueChanged(Slider* slider)
{
    if(slider->getComponentID().compare("player_vol_slider") == 0)
    {
        player->setGain(slider->getValue());
    }
}

bool Mediator::keyPressed(const KeyPress& key, Component* originatingComponent)
{
    if(originatingComponent == audioPlayerControls.get())
    {
        if(key.getKeyCode() == KeyPress::spaceKey)
        {
            if(player->getPlayerState() == AudioPlayer::TransportState::playing)
            {
                player->pause();
                audioPlayerControls->setPlayButtonState(PlayerGUIButton::ControlType::play);
                Timer::stopTimer();
            }
            else if(player->getPlayerState() == AudioPlayer::TransportState::paused)
            {
                playIndex(currentPlayingIndex, false);
            }
        }
        return true;
    }
    
    return false;
}

void Mediator::timerCallback()
{
    audioPlayerControls->setPercentageThroughTrack(player->getPosAsPercentageOfTrackLen());

    audioPlayerControls->setTimeThroughTrack(std::chrono::duration<int, std::ratio<1>>(int(player->getCurrentPos())));
}

bool Mediator::addNewFiles()
{
    if(initialiser.lookForNewFiles())
    {
        dataHandler->addData(initialiser.getResult());
        initialiser.clearCurrentFiles();
        dataHandler->sort();
        return true;
    }
    return false;
}

void Mediator::playIndex(int index, bool ignorePause)
{
    if(index >= 0 && index < getNumberOfRowsToDisplay() - 1)
    {
        if(index != currentPlayingIndex || ignorePause == true)
        {
            player->stop();
            MetadataReader* newFile = dataHandler->getReaderForIndex(index);
            
            player->loadFile(newFile->getFile());
            
            if(newFile->getArtwork() != nullptr)
            {
                audioPlayerControls->setArtworkToShow(*newFile->getArtwork());
            }
            
            audioPlayerControls->setTitleLabelText(dataHandler->getDataForItem(DataHandler::DataConcerned::trackTitle, index));
            
            audioPlayerControls->setLengthOfTrack(std::chrono::duration<int, std::ratio<1>>(int(player->getCurrentTrackLength())));
        }
        player->play();
        audioPlayerControls->setPlayButtonState(PlayerGUIButton::ControlType::pause);
        currentPlayingIndex = index;
        Timer::startTimer(100);
    }
    else
    {
        stopPlayer();
        audioPlayerControls->setTitleLabelText("");
    }
}

void Mediator::showPlayer(bool show)
{
    playerWindow->setVisible(show);
    menu->setPlayerWindowOpen(show);
    
    if(!show)
    {
        stopPlayer();
    }
}

void Mediator::stopPlayer()
{
    Timer::stopTimer();
    player->stop();
    audioPlayerControls->setPlayButtonState(PlayerGUIButton::ControlType::play);
    currentPlayingIndex = 0;
}
