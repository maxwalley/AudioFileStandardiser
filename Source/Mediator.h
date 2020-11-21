/*
  ==============================================================================

    Mediator.h
    Created: 22 Jun 2020 3:22:25pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Logger.h"
#include "FileInitialiser.h"
#include "DataHandler.h"
#include "TableModel.h"
#include "MenuModel.h"
#include "BatchControlsImplementation.h"
#include "BatchRenameControls.h"
#include "FileAndDirectoryControls.h"
#include "AudioPlayerGUI.h"
#include "AudioPlayer.h"
#include "AudioPlayerListener.h"
#include "ComponentWindow.h"
#include "MainWindow.h"
#include "ChronoTimeToStringConverter.h"
#include "NewMainComponent.h"

class Mediator  :   public ActionListener,
                    public Button::Listener,
                    public TextEditor::Listener,
                    public MouseListener,
                    public AudioPlayerListener,
                    public Slider::Listener,
                    public KeyListener,
                    public Timer,
                    public NewMainComponent::Listener,
                    public TableHeaderComponent::Listener
{
public:
    
    Mediator();
    ~Mediator();
    
    NewMainComponent* getMainComponent();
    
    void initialiseComponents();
    
    TableModel* getTableModel();
    
    DataHandler* getDataHandler();
    
    BatchRenameControls* getBatchControls();
    
    FileAndDirectoryControls* getFileAndDirectoryControls();
    
    AudioPlayerGUI* getAudioPlayerControls();
    
    int getNumberOfRowsToDisplay();
    String getDataForCell(int rowNumber, int column);
    bool getSelectedForRow(int rowNumber);
    
    void setDataForCell(int rowNumber, int column, const String& newData);
    
    StringArray getSupportedFileTypes() const;
    
private:
    
    int currentPlayingIndex;
    
    void actionListenerCallback (const String &message) override;
    
    void buttonClicked(Button* button) override;
    
    void textEditorTextChanged(TextEditor& editor) override;
    
    void mouseDown(const MouseEvent& event) override;
    
    void playerFinished(AudioPlayer* playerThatHasFinished) override;
    
    void sliderValueChanged(Slider* slider) override;
    
    bool keyPressed(const KeyPress& key, Component* originatingComponent) override;
    
    void timerCallback() override;
    
    void filesDropped(const StringArray& files) override;
    
    void tableColumnsChanged(TableHeaderComponent* tableHeader) override;
    
    void tableColumnsResized(TableHeaderComponent* tableHeader) override;
    
    void tableSortOrderChanged(TableHeaderComponent* tableHeader) override {};
    
    FileInitialiser initialiser;
    
    std::unique_ptr<DataHandler> dataHandler;
    
    bool addNewFiles(const Array<File>& filesToAdd = Array<File>());
    
    void playIndex(int index, bool ignorePause);
    
    void showPlayer(bool show);
    
    void stopPlayer();
    
    void calculateMainWindowSizes();
    
    std::unique_ptr<MenuModel> menu;
    
    //This can't be a unique pointer because it is an incomplete type - can be done but complicated
    NewMainComponent* mainComponent;
    
    std::unique_ptr<TableModel> tableModel;
    
    std::unique_ptr<BatchControlsImplementation> batchControlsImp;
    
    std::unique_ptr<BatchRenameControls> batchControls;
    
    std::unique_ptr<FileAndDirectoryControls> fileControls;
    
    std::unique_ptr<AudioPlayerGUI> audioPlayerControls;
    
    std::unique_ptr<AudioPlayer> player;
    
    std::unique_ptr<ComponentWindow> playerWindow;
    
    std::unique_ptr<MainWindow> mainWindow;
};
