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

    /* Note: Be careful if you override any DocumentWindow methods - the base
       class uses a lot of them, so by overriding you might break its functionality.
       It's best to do all your work in your content component instead, but if
       you really have to override any DocumentWindow methods, make sure your
       subclass also calls the superclass's method.
    */

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
