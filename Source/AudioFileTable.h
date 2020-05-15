/*
  ==============================================================================

    AudioFileTable.h
    Created: 2 May 2020 5:25:10pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Edit Metadata Window/EditMetadataWindow.h"
#include "tag_c.h"

//==============================================================================
/*
*/
class TagLib_TagSorter
{
public:
    int compareElements(TagLib_Tag* first, TagLib_Tag* second);
};



class AudioFileTable    :   public Component,
                            public TableListBoxModel,
                            public Button::Listener,
                            public Label::Listener
{
public:
    AudioFileTable();
    ~AudioFileTable();

    void paint (Graphics&) override;
    void resized() override;

    void setFiles(Array<File> filesToShow);
    
    void refreshTable();
    
    int getTableHeight();
    
private:
    
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    void buttonClicked(Button* button) override;
    
    void labelTextChanged(Label* label) override;
    
    TableListBox table;
    
    Array<TagLib_Tag*> metadataArray;
    TagLib_TagSorter arraySorter;
    
    String fileExtension;
    
    TextButton editMetadataButton;
    
    EditMetadataWindow* metadataWindow;
    
    Array<ToggleButton*> selectionButtons;
    Array<Label*> trackNumLabels;
    Array<Label*> trackNameLabels;
    Array<Label*> artistNameLabels;
    Array<Label*> albumNameLabels;
    Array<Label*> yearLabels;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFileTable)
};
