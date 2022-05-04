/*
  ==============================================================================

    BatchControlsImplementation.h
    Created: 1 Jul 2020 5:31:53pm
    Author:  Max Walley

  ==============================================================================
*/

//This class receives strings and will process them according to the settings held in the batch controls GUI

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "BatchRenameControls.h"
#include "StringChecker.h"

class BatchControlsImplementation
{
public:
    
    BatchControlsImplementation(BatchRenameControls* batchGUIControls);
    ~BatchControlsImplementation();
    
    BatchRenameControls::ButtonsActive getActiveDataButtons() const;
    
    String manipulateStringAccordingToGUI(const String& inputString);
    
private:
    BatchRenameControls* guiControls;
    
    
};
