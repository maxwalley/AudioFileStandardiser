/*
  ==============================================================================

    WAVINFOMetadataReader.cpp
    Created: 30 May 2020 11:55:44am
    Author:  Max Walley

  ==============================================================================
*/

#include "WAVINFOMetadataReader.h"

WAVINFOMetadataReader::WAVINFOMetadataReader(AudioFormatReader* juceReader)
{
    if(juceReader->getFormatName().compare("WAV") != 0)
    {
        
    }
}
