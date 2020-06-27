/*
  ==============================================================================

    LookAndFeels.cpp
    Created: 26 Jun 2020 8:58:44pm
    Author:  Max Walley

  ==============================================================================
*/

#include "LookAndFeels.h"

void TableTextEditorLAndF::drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& editor)
{
    Path path;
    
    path.startNewSubPath(width, 0);
    path.lineTo(width, height);
    path.lineTo(0, height);
    
    g.strokePath(path, PathStrokeType(1.0f));
}
