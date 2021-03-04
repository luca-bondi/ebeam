/*
  ==============================================================================

    RoundLed.cpp
    Created: 3 Mar 2021 8:18:08pm
    Author:  Luca Bondi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RoundLed.h"

void RoundLed::paint(Graphics &g) {
    
    Rectangle<float> area = getLocalBounds().toFloat();
    auto side = area.getHeight() > area.getWidth() ? area.getWidth() : area.getHeight();
    auto ctr = area.getCentre();
    area = Rectangle<float>(side, side);
    area.setCentre(ctr);
    
    g.setColour(colour);
    g.fillEllipse(area);
}

void RoundLed::resized() {
    
}
