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

class NewMainComponent;

class Mediator  :   public ActionListener,
                    public Button::Listener,
                    public TextEditor::Listener,
                    public MouseListener,
                    public AudioPlayerListener,
                    public Slider::Listener,
                    public KeyListener,
                    public Timer
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
    
    virtual int getNumberOfRowsToDisplay();
    virtual String getDataForCell(int rowNumber, int column);
    virtual bool getSelectedForRow(int rowNumber);
    
    virtual void setDataForCell(int rowNumber, int column, const String& newData);
    
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
    
    FileInitialiser initialiser;
    
    std::unique_ptr<DataHandler> dataHandler;
    
    bool addNewFiles();
    
    void playIndex(int index, bool ignorePause);
    
    void showPlayer(bool show);
    
    void stopPlayer();
    
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
};
