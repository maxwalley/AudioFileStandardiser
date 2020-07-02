/*
  ==============================================================================

    MenuModel.h
    Created: 29 Jun 2020 6:11:24pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MenuModel :   public MenuBarModel,
                    public ActionBroadcaster
{
public:
    MenuModel();
    ~MenuModel();
    
    enum class MenuNames
    {
        File,
        View
    };
    
    void setMenuItemVisible(MenuNames menuName, bool setVisible, int index = -1);
    
    void setBatchControlsShown(bool set);
    bool getBatchControlsShown() const;
    
    void setFileControlsShown(bool set);
    bool getFileControlsShown() const;
    
private:
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
    
    StringArray menuNames;
    
    String menuNamesToString(MenuNames menuName);
    
    bool batchControlsShown;
    bool fileAndFolderControlsShown;
};
