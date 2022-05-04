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
    String newString = inputString;
    
    if(guiControls->getCharsToRemove())
    {
        //Removes characters set by the batch controls
        newString = newString.replace(*guiControls->getCharsToRemove(), "");
    }
    
    if(guiControls->getNumStartCharsToRemove())
    {
        //Removes start chars set by batch controls from titles
        newString = newString.substring(*guiControls->getNumStartCharsToRemove());
    }
    
    if(guiControls->getNumEndCharsToRemove())
    {
        //Removes end chars set by batch controls from titles
        newString = newString.dropLastCharacters(*guiControls->getNumEndCharsToRemove());
    }
    
    if(guiControls->getCharsToAddToStart())
    {
        //Adds start chars set by batch controls from titles
        newString = newString.replaceSection(0, 0, *guiControls->getCharsToAddToStart());
    }
    
    if(guiControls->getCharsToAddToPosition() && guiControls->getPositionToAdd())
    {
        //If the position is more than the length of the string
        if(guiControls->getPositionToAdd() > newString.length())
        {
            newString += *guiControls->getCharsToAddToPosition();
        }
        
        //Adds string into a position
        else
        {
            newString = newString.replaceSection(*guiControls->getPositionToAdd(), 0, *guiControls->getCharsToAddToPosition());
        }
    }
    
    if(guiControls->getCharsToAddToEnd())
    {
        //Adds end chars set by batch controls from titles
        newString += *guiControls->getCharsToAddToEnd();
    }
    
    if(guiControls->getCharToReplace() && guiControls->getCharToReplaceWith())
    {
        //Replaces char with another char both set by batch controls
        newString = newString.replace(*guiControls->getCharToReplace(), *guiControls->getCharToReplaceWith());
    }
    
    //Checks if the default capatalisation settings in batch control is set. If not it'll check the state of the other batch control settings
    if(guiControls->getDefaultCapSettings())
    {
        newString = newString.toLowerCase();
        
        newString = StringChecker::capatalizeFirstLetters(newString);
        
        newString = StringChecker::decapatalizeWords(newString);
    }
    else
    {
        //Capatalises or decapatalises all words based on what is toggled in batch controls
        if(guiControls->getCapAllWords())
        {
            newString = newString.toUpperCase();
        }
        
        else if(guiControls->getDecapAllWords())
        {
            newString = newString.toLowerCase();
        }
        
        if(guiControls->getCapWord())
        {
            String tempString = *guiControls->getCapWord();
            
            //Capatalises a certain word set by batch controls
            newString = newString.replace(tempString, tempString.toUpperCase());
        }
        
        //Capatalises the start of all words or just one specific one based on the options set by batch controls
        if(guiControls->getCapStartOfAllWords())
        {
            newString = StringChecker::capatalizeFirstLetters(newString);
        }
        //Capatalises the start of just one word
        else if(guiControls->getCapStartOfWord())
        {
            newString = newString.replace(*guiControls->getCapStartOfWord(), StringChecker::capatalizeFirstLetters(*guiControls->getCapStartOfWord()));
        }
    }
    
    
    return newString;
}
