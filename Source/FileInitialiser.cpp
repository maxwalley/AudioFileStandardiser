/*
  ==============================================================================

    FileInitializer.cpp
    Created: 22 Jun 2020 4:54:12pm
    Author:  Max Walley

  ==============================================================================
*/

#define SUPPORTEDTYPES "*.mp3;*.flac;*.wav;*.wave;*.aac;*.wma;*.aif;*.m4a"

#include "FileInitialiser.h"

#include "Mediator.h"

FileInitialiser::FileInitialiser()  :   hasOwnership(false)
{
    
}

FileInitialiser::~FileInitialiser()
{
    clearCurrentFiles();
}

bool FileInitialiser::lookForNewFiles()
{
    FileChooser chooser("Pick a folder", File(), "*.zip;*.mp3;*.flac;*.wav;*.wave;*.aac;*.wma;*.aif;*.m4a", true, false, nullptr);
    
    //Looks and opens the file
    if(!chooser.browseForMultipleFilesOrDirectories())
    {
        return false;
    }
    
    Array<File> chosenFiles = chooser.getResults();
    
    for(int i = 0; i < chosenFiles.size(); i++)
    {
        if(chosenFiles[i].hasFileExtension(".zip"))
        {
            chosenFiles.set(i, decompressZipToLocation(chosenFiles[i]));
        }
        
        if(chosenFiles[i].isDirectory())
        {
            Array<File> tempArray = chosenFiles[i].findChildFiles(2, true, SUPPORTEDTYPES);
            chosenFiles.remove(i);
            chosenFiles.insertArray(i, tempArray.data(), tempArray.size());
        }
    }
    
    if(chosenFiles.size() == 0)
    {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, "No Suitable Files Detected", "The folder you have selected contains no supported file types");
            
        return false;
    }
    
    for(int i = 0; i < chosenFiles.size(); i++)
    {
        std::unique_ptr<AudioMetadataReader> currentReader = metadataManager.createMetadataReader(chosenFiles[i]);
                
        //If it = null pointer
        if(!currentReader)
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "File Error", "The file: " + chosenFiles[i].getFileName() + " does not use supported metadata and will not be included");
            
            chosenFiles.remove(i);
            
            i--;
            
            if(chosenFiles.size() == 0)
            {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Error - All files are incompatible", "None of the files in the selected folder have compatable metadata objects");
                
                return false;
            }
        }
        else
        {
            currentFiles.push_back(std::move(currentReader));
        }
    }
    hasOwnership = true;
    return true;
}

std::vector<std::unique_ptr<AudioMetadataReader>>& FileInitialiser::getResult()
{
    hasOwnership = false;
    return currentFiles;
}

File FileInitialiser::decompressZipToLocation(const File& zip)
{
    if(zip.exists() && zip.getFileExtension().compare(".zip") == 0)
    {
        ZipFile file(zip);
            
        String newDirName = zip.getParentDirectory().getFullPathName() + "/" + zip.getFileNameWithoutExtension();
        
        if(File(newDirName).isDirectory())
        {
            if(!AlertWindow::showNativeDialogBox("Duplicate folder names", "A folder with this name already exists in this directory, would you like a similar name to be allocated?", true))
            {
                return zip;
            }
            
            bool nameFound = false;
            for(int i = 0; !nameFound; i++)
            {
                if(!File(newDirName + " (" + String(i+1) + ")").isDirectory())
                {
                    newDirName = newDirName + " (" + String(i+1) + ")";
                    nameFound = true;
                }
            }
        }
        
        file.uncompressTo(newDirName);
        return File(newDirName);
    }
    return zip;
}

void FileInitialiser::clearCurrentFiles()
{
    currentFiles.clear();
}
