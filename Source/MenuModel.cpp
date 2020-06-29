/*
  ==============================================================================

    MenuModel.cpp
    Created: 29 Jun 2020 6:11:24pm
    Author:  Max Walley

  ==============================================================================
*/

#include "MenuModel.h"

MenuModel::MenuModel()
{
    setMacMainMenu(this);
}

MenuModel::~MenuModel()
{
    setMacMainMenu(nullptr);
}

StringArray MenuModel::getMenuBarNames()
{
    StringArray menuNames("File", "Settings");
    
    /*if fileLoaded menuNames.add("view")*/
    
    return menuNames;
    
}

PopupMenu MenuModel::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
    PopupMenu menu;
    
    if(topLevelMenuIndex == 0)
    {
        menu.addItem(1, "Add new files", true, false);
    }
    
    else if(topLevelMenuIndex == 2)
    {
        //menu.addItem(1, "Add new files", true, false);
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
}
