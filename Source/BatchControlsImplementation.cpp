/*
  ==============================================================================

    BatchControlsImplementation.cpp
    Created: 1 Jul 2020 5:31:53pm
    Author:  Max Walley

  ==============================================================================
*/

#include "BatchControlsImplementation.h"

BatchControlsImplementation::BatchControlsImplementation(BatchRenameControls* batchGUIControls) :   guiControls(batchGUIControls)
{
    
}

BatchControlsImplementation::~BatchControlsImplementation()
{
    
}

BatchRenameControls::ButtonsActive BatchControlsImplementation::getActiveDataButtons() const
{
    return guiControls->getButtonsActive();
}

String BatchControlsImplementation::manipulateStringAccordingToGUI(const String& inputString)
{
    String newString = inputString.toUpperCase();
    
    return newString;
}

void BatchControlsImplementation::test()
{
    DBG(int(guiControls->getButtonsActive() & BatchRenameControls::titleButton));
    DBG(int(guiControls->getButtonsActive() & BatchRenameControls::artistButton));
    DBG(int(guiControls->getButtonsActive() & BatchRenameControls::albumButton));
    
    DBG(guiControls->getCharsToRemove().value_or("false"));
}
