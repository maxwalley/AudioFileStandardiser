/*
  ==============================================================================

    MainWindow.cpp
    Created: 22 Jul 2020 6:46:48pm
    Author:  Max Walley

  ==============================================================================
*/

#include "MainWindow.h"

MainWindow::MainWindow(String name) :   DocumentWindow(name, Colours::grey, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);

    setResizable(true, true);
    centreWithSize(getWidth(), getHeight());
    setResizeLimits(10, 10, 2000, 2000);

    setVisible(true);
}

void MainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
