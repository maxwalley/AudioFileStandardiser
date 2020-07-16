/*
  ==============================================================================

    FileAndFolderCreator.cpp
    Created: 16 Jul 2020 3:23:24pm
    Author:  Max Walley

  ==============================================================================
*/

#include "FileAndFolderCreator.h"

FileAndFolderCreator::FileAndFolderCreator()
{
    
}

FileAndFolderCreator::~FileAndFolderCreator()
{
    
}

std::optional<File> FileAndFolderCreator::createNewFolder(String newLocation)
{
    if(File(newLocation).exists())
    {
        if(!AlertWindow::showNativeDialogBox("Duplicate folder names", "An item with this name already exists in this directory, would you like a similar name to be allocated?", true))
        {
            return std::nullopt;
        }
        
        for(int i = 0; i!=-1; i++)
        {
            String newName;
            
            //If the taken file was a file
            if(File(newLocation).existsAsFile())
            {
                int extensionStart = newLocation.lastIndexOf(".");
                
                newName = newLocation.replaceSection(extensionStart, 0, " (" + String(i+1) + ")");
            }
            
            //If the taken file was a folder
            else
            {
                newName = newLocation + " (" + String(i+1) + ")";
            }
            
            if(!File(newName).exists())
            {
                return File(newName);
            }
        }
    }
    return File(newLocation);
}
