/*
  ==============================================================================

    FileInitializer.cpp
    Created: 22 Jun 2020 4:54:12pm
    Author:  Max Walley

  ==============================================================================
*/

#include "FileInitialiser.h"

FileInitialiser::FileInitialiser(const StringArray& supportedFileTypes)  : supportedTypes(supportedFileTypes)
{
    supportedTypesInOne = convertSupportedTypesToString();
}

FileInitialiser::~FileInitialiser()
{
    clearCurrentFiles();
}

bool FileInitialiser::lookForNewFilesAndAdd()
{
    FileChooser chooser("Pick a folder", File(), "*.zip;" + supportedTypesInOne, true, false, nullptr);
    
    //Looks and opens the file
    if(!chooser.browseForMultipleFilesOrDirectories())
    {
        return false;
    }
    
    return addNewFiles(chooser.getResults());
}

bool FileInitialiser::addNewFiles(const Array<File>& files)
{
    Array<File> chosenFiles(files);
    
    for(int i = 0; i < chosenFiles.size(); i++)
    {
        if(chosenFiles[i].hasFileExtension(".zip"))
        {
            std::optional<File> decompressedFolder = decompressZipToLocation(chosenFiles[i]);
            
            //If something went wrong in decompression
            if(decompressedFolder == std::nullopt)
            {
                chosenFiles.remove(i);
                i--;
                
                if(chosenFiles.isEmpty())
                {
                    return false;
                }
            }
            else
            {
                chosenFiles.set(i, *decompressedFolder);
            }
        }
        
        if(chosenFiles[i].isDirectory())
        {
            Array<File> tempArray = chosenFiles[i].findChildFiles(2, true, supportedTypesInOne);
            chosenFiles.remove(i);
            chosenFiles.insertArray(i, tempArray.data(), tempArray.size());
        }
    }
    
    if(chosenFiles.size() == 0)
    {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, "No Suitable Files Detected", "The locationss you have selected contains no supported file types");
            
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
    return true;
}

std::vector<std::unique_ptr<AudioMetadataReader>>& FileInitialiser::getResult()
{
    return currentFiles;
}

void FileInitialiser::clearCurrentFiles()
{
    currentFiles.clear();
}

StringArray FileInitialiser::getSupportedFileTypes() const
{
    return supportedTypes;
}

std::optional<File> FileInitialiser::decompressZipToLocation(const File& zip)
{
    if(zip.exists() && zip.getFileExtension().compare(".zip") == 0)
    {
        ZipFile file(zip);
            
        String newDirName = zip.getParentDirectory().getFullPathName() + "/" + zip.getFileNameWithoutExtension();
        
        std::optional<File> newFolder = FileAndFolderCreator::createNewFolder(newDirName);
        
        if(newFolder == std::nullopt)
        {
            return std::nullopt;
        }
        
        file.uncompressTo(*newFolder);
        return File(newDirName);
    }
    return zip;
}

String FileInitialiser::convertSupportedTypesToString()
{
    String convertedOutput;
    
    std::for_each(supportedTypes.begin(), supportedTypes.end(), [&convertedOutput](const String& str)
    {
        convertedOutput += "*" + str + ";";
    });
    
    return convertedOutput;
}
