/*
  ==============================================================================

    AudioFileTable.h
    Created: 2 May 2020 5:25:10pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//#include "tag_c.h"
#include "StringChecker.h"
#include "BatchRenameControls.h"
#include "AudioMetadataManager.h"
#include "TableCellComponent.h"
#include "FileAndDirectoryControls.h"

//==============================================================================
/*
*/
class MetadataReaderSorter
{
public:
    int compareElements(AudioMetadataReader* first, AudioMetadataReader* second);
};

class TextEditorOutlineDrawer   :   public LookAndFeel_V4
{
public:
    void drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& editor) override;
};


class AudioFileTable    :   public Component,
                            public TableListBoxModel,
                            public Button::Listener,
                            public TextEditor::Listener,
                            public ActionListener,
                            public ActionBroadcaster
{
public:
    AudioFileTable();
    ~AudioFileTable();
    
    void paint (Graphics&) override;
    void resized() override;

    bool setFiles();
    
    int getTableHeight();
    
    void setFileNamesToChangeWithTitle(bool change);
    
    void setBatchControlsVisible(bool visible);
    
    void addExtraInfoActionListener(ActionListener* listener);
    
    void changeFiles();
    
    bool getIfFileLoaded();
    
    void setFileAndDirectoryControlsVisible(bool visible);
    
private:
    
    
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    void buttonClicked(Button* button) override;
    
    void textEditorTextChanged (TextEditor& editor) override;

    void actionListenerCallback(const String& message) override;
    
    void changeMetadataForCellComponent(int cellColumn, int row, const String& newData);
    
    bool isAnyTableButtonOn();
    
    void sendDirectoryDataToControls();
    
    void changeFileNamesToTitles();
    
    File decompressZipToLocation(File zip);
    
    String getValueForCell(int row, int column);
    
    TableListBox table;
    
    MetadataReaderSorter arraySorter;
    
    AudioMetadataManager metadataManager;
    OwnedArray<AudioMetadataReader> metadataReaders;
    
    Array<bool> selectionButtonsValues;
    
    TextEditorOutlineDrawer drawer;
    
    bool fileNamesToChangeWithTitle;
    
    Viewport extraInfoViewport;
    BatchRenameControls batchControls;
    bool showBatchControls;
    
    bool fileLoaded;
    
    bool fileAndFolderControlsVisible;
    
    FileAndDirectoryControls fileAndDirectoryControls;
    
    TextButton testButt;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFileTable)
};
