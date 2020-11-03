/*
  ==============================================================================

    MainWindow.h
    Created: 22 Jul 2020 6:46:48pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

/*
    This class implements the desktop window that contains an instance of
    our MainComponent class.
*/
class MainWindow    : public DocumentWindow
{
public:
    MainWindow(String name);

    void closeButtonPressed() override;

    //adjust main component for scroll bar

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
