/*
  ==============================================================================

    AudioFileTable.h
    Created: 2 May 2020 5:25:10pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "mpegfile.h"
#include "tag.h"
#include "tag_c.h"

//==============================================================================
/*
*/
class TagLib_TagSorter
{
public:
    int compareElements(TagLib_Tag* first, TagLib_Tag* second);
};



class AudioFileTable    : public Component,
                          public TableListBoxModel
{
public:
    AudioFileTable();
    ~AudioFileTable();

    void paint (Graphics&) override;
    void resized() override;

    void setFiles(Array<File> filesToShow);
    
    void refreshTable();
    
private:
    
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    
    TableListBox table;
    TableHeaderComponent header;
    
    OwnedArray<TagLib_Tag> metadataArray;
    TagLib_TagSorter arraySorter;
    
    String fileExtension;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFileTable)
};
