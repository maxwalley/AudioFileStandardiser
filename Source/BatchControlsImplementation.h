/*
  ==============================================================================

    BatchControlsImplementation.h
    Created: 1 Jul 2020 5:31:53pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "BatchRenameControls.h"

class BatchControlsImplementation
{
public:
    BatchControlsImplementation(BatchRenameControls* batchGUIControls);
    ~BatchControlsImplementation();
    
    void test();
    
private:
    BatchRenameControls* guiControls;
    
    
};
