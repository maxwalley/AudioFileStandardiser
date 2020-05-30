/*
  ==============================================================================

    AudioFileTable.h
    Created: 2 May 2020 5:25:10pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "tag_c.h"
#include "StringChecker.h"
#include "BatchRenameControls.h"
#include "FormatMetadataManager.h"

//==============================================================================
/*
*/
class TagLib_TagSorter
{
public:
    int compareElements(TagLib_Tag* first, TagLib_Tag* second);
};

class MetadataReaderSorter
{
public:
    int compareElements(FormatMetadataReader* first, FormatMetadataReader* second);
};



class AudioFileTable    :   public Component,
                            public TableListBoxModel,
                            public Button::Listener,
                            public Label::Listener,
                            public ActionListener
{
public:
    AudioFileTable();
    ~AudioFileTable();

    void paint (Graphics&) override;
    void resized() override;

    void setFiles(Array<File>& filesToShow);
    
    void refreshTable();
    
    int getTableHeight();
    
    void setFileNamesToChangeWithTitle(bool change);
    
    void setBatchControlsVisible(bool visible);
    
    void addBatchControlsActionListener(ActionListener* listener);
    
private:
    
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    void buttonClicked(Button* button) override;
    
    void labelTextChanged(Label* label) override;
    
    void saveTableToTags();
    
    void actionListenerCallback(const String& message) override;
    
    TableListBox table;
    
    Array<File> juceFiles;
    Array<TagLib_File*> metadataFiles;
    
    Array<TagLib_Tag*> metadataArray;
    //TagLib_TagSorter arraySorter;
    MetadataReaderSorter arraySorter;
    
    FormatMetadataManager metadataManager;
    OwnedArray<FormatMetadataReader> metadataReaders;
    
    String fileExtension;
    
    TextButton correctDataButton;
    TextButton saveButton;
    TextButton changeLocationButton;
    
    
    Array<ToggleButton*> selectionButtons;
    Array<Label*> trackNumLabels;
    Array<Label*> trackNameLabels;
    Array<Label*> artistNameLabels;
    Array<Label*> albumNameLabels;
    Array<Label*> yearLabels;
    
    String currentDirectoryPath;
    
    bool fileNamesToChangeWithTitle;
    
    Viewport batchControlViewport;
    BatchRenameControls batchControls;
    bool showBatchControls;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFileTable)
};
