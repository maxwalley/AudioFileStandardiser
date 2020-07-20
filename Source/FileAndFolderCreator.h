/*
  ==============================================================================

    FileAndFolderCreator.h
    Created: 16 Jul 2020 3:23:24pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <optional>

class FileAndFolderCreator
{
public:
    FileAndFolderCreator();
    ~FileAndFolderCreator();
    
    //Creates a new file or folder but checks if one is currently there and displays and error message if there is
    static std::optional<File> createNewFolder(String newLocation);
};
