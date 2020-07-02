/*
  ==============================================================================

    MenuModel.cpp
    Created: 29 Jun 2020 6:11:24pm
    Author:  Max Walley

  ==============================================================================
*/

#include "MenuModel.h"

MenuModel::MenuModel()  :   menuNames("File"), batchControlsShown(false)
{
    setMacMainMenu(this);
}

MenuModel::~MenuModel()
{
    setMacMainMenu(nullptr);
}

void MenuModel::setMenuItemVisible(MenuNames menuName, bool setVisible, int index)
{
    String menuNameToSet = menuNamesToString(menuName);
    
    //Checks that the array doesn't already contain it
    if(setVisible == true && !menuNames.contains(menuNameToSet))
    {
        menuNames.insert(index, menuNamesToString(menuName));
    }
    
    else
    {
        menuNames.removeString(menuNamesToString(menuName));
    }
}

void MenuModel::setBatchControlsShown(bool set)
{
    batchControlsShown = set;
}

bool MenuModel::getBatchControlsShown() const
{
    return batchControlsShown;
}

void MenuModel::setFileControlsShown(bool set)
{
    fileAndFolderControlsShown = set;
}

bool MenuModel::getFileControlsShown() const
{
    return fileAndFolderControlsShown;
}

StringArray MenuModel::getMenuBarNames()
{
    return menuNames;
}

PopupMenu MenuModel::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
    PopupMenu menu;
    
    if(menuName.compare("File") == 0)
    {
        menu.addItem(1, "Add new files", true, false);
    }
    
    else if(menuName.compare("View") == 0)
    {
        menu.addItem(10, "Show Batch Controls", true, batchControlsShown);
        menu.addItem(11, "Show File and Folder Controls", true, fileAndFolderControlsShown);
    }
    
    return menu;
}

void MenuModel::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    //Alternative for this would be for items to just send their item id alongside menu index to reduce checks
    
    if(topLevelMenuIndex == 0)
    {
        if(menuItemID == 1)
        {
            sendActionMessage("menu_add_files");
        }
    }
    
    else if(menuItemID == 10)
    {
        sendActionMessage("menu_show_batch");
        batchControlsShown = !batchControlsShown;
    }
    
    else if(menuItemID == 11)
    {
        sendActionMessage("menu_show_file_controls");
        fileAndFolderControlsShown = !fileAndFolderControlsShown;
    }
}

String MenuModel::menuNamesToString(MenuNames menuName)
{
    switch (menuName)
    {
        case MenuNames::File:
            return "File";
            break;
            
        case MenuNames::View:
            return "View";
            break;
    }
}
