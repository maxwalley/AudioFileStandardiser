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

class NewMainComponent;

class Mediator  :   public ActionListener,
                    public Button::Listener,
                    public TextEditor::Listener
{
public:
    
    static Mediator* getInstance();
    
    static void closeInstance();
    
    NewMainComponent* getMainComponent();
    
    void initialiseComponents();
    
    TableModel* getTableModel();
    
    static DataHandler* getDataHandler();
    
    BatchRenameControls* getBatchControls();
    
    virtual int getNumberOfRowsToDisplay();
    virtual String getDataForCell(int rowNumber, int column);
    virtual bool getSelectedForRow(int rowNumber);
    
    virtual void setDataForCell(int rowNumber, int column, const String& newData);
    
private:
    Mediator(){};
    
    static Mediator* instance;
    
    void actionListenerCallback (const String &message) override;
    
    void buttonClicked(Button* button) override;
    
    void textEditorTextChanged(TextEditor& editor) override;
    
    FileInitialiser initialiser;
    
    static DataHandler dataHandler;
    
    void addNewFiles();
    
    std::unique_ptr<MenuModel> menu;
    
    //This can't be a unique pointer because it is an incomplete type - can be done but complicated
    NewMainComponent* mainComponent;
    
    std::unique_ptr<TableModel> tableModel;
    
    std::unique_ptr<BatchControlsImplementation> batchControlsImp;
    
    std::unique_ptr<BatchRenameControls> batchControls;
};
