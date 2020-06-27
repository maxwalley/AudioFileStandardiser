/*
  ==============================================================================

    LookAndFeels.h
    Created: 26 Jun 2020 8:58:44pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TableTextEditorLAndF   :   public LookAndFeel_V4
{
public:
    void drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& editor) override;
};
