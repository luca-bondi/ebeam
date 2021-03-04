/*
  ==============================================================================

    RoundLed.h
    Created: 3 Mar 2021 8:18:08pm
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

//==============================================================================
/*
*/
class RoundLed : public Component {
public:
    
    RoundLed() {};
    
    Colour colour;
    
    void paint(Graphics &) override;
    
    void resized() override;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RoundLed)
};
