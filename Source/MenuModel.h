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
    
private:
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
};
